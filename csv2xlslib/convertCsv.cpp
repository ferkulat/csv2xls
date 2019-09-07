//
// Created by marcel on 9/5/19.
//
#include "convertCsv.h"
#include "funcomp.h"
#include "readBuffer.h"
#include <fstream>
#include "MatchVariantType.h"
#include "Helpers.h"
#include <algorithm>
namespace csv2xls
{

using funcomp::operator|;
using funcomp::repeatUntil;

struct Ok{};
namespace Domain
{
using ParseResult = std::variant<Row, EndOfStream, Ok>;

auto fill(Buffer& buffer, std::istream& csv_input)-> ParseResult
{
    if (!csv_input.good())
        return EndOfStream{};

    auto const bytes_left    = buffer.end - buffer.mem.get();
    auto const bytes_to_read = buffer.m_size.Get() - bytes_left;

    csv_input.read(buffer.end, bytes_to_read);

    auto const bytes_read = csv_input.gcount();
    buffer.end += bytes_read;
    if (bytes_read < bytes_to_read)
    {
        *buffer.end = '\0';
        ++(buffer.end);
    }
    return Ok{};
}

auto fillWith(std::istream& csv_input)
{
    return [&](Buffer& buffer)
    {
      return fill(buffer, csv_input);
    };
}

auto CopyCellToStartOf(Buffer& buffer, EndOfBuffer eob)->Buffer&
{
    buffer.current_position = buffer.mem.get();
    if (eob.unfinished_cell)
    {
        auto const cell = eob.unfinished_cell.value();
        std::copy(cell.cbegin(), cell.cend(), buffer.current_position );
        buffer.end = buffer.current_position + cell.length();
        buffer.quoted = '\0';
    }
    else
    {
        buffer.end = buffer.mem.get();
    }
    return buffer;
}

auto CopyCellToStartOf (Buffer& buffer)
{
    return [&](EndOfBuffer eob)->Buffer&
    {
      return CopyCellToStartOf(buffer, eob);
    };
}

template<typename PrepareBuffer>
auto appendToOutputDoc(PrepareBuffer& prepareBuffer, OutputDoc& output_doc, CsvType csv_type)
{
    using R = ParseResult;
    return MatchType(csv_type
        , [&](CellContent cell) -> R { output_doc.appendCell(cell); return Ok{}; }
        , [&](EndOfLine   eol ) -> R { output_doc.appendCell(eol.cell);return output_doc.newLine(); }
        , [&](EndOfBuffer eob ) -> R { return prepareBuffer(eob);}
        , [&](EndOfStream eos ) -> R { prepareBuffer(EndOfBuffer{});return eos; }
    );
}

}

namespace ChainingAdaptors
{
auto appendTo(Buffer& buffer, std::istream& csv_input, OutputDoc& output_doc)
{
    auto prepareBuffer = Domain::CopyCellToStartOf(buffer)|Domain::fillWith(csv_input);

    return [prepareBuffer,&output_doc](CsvType csv_type) {
      return Domain::appendToOutputDoc(prepareBuffer, output_doc, csv_type);
    };
}
}

auto isRowLimit (std::optional<OutputRowLimit> output_row_limit)
{
    return [output_row_limit](Row row) {
      return (output_row_limit)? row.isGreaterEqual(output_row_limit.value()):false;
    };
}

std::optional<OutputDoc>
convertCsv(Buffer& buffer, Parameter const& parameter, std::istream& stream, std::optional<OutputDoc> output_doc)
{
    if (!stream.good()&& buffer.empty())
        return std::nullopt;

    auto appendTo = [&buffer, &stream](OutputDoc& output)
    {
      return ChainingAdaptors::appendTo(buffer, stream, output);
    };
    auto thereIsNothingToParse = matchesOneOf(isType<EndOfStream>{},isRowLimit(parameter.output_row_limit));
    auto parse = read
                 | appendTo(*output_doc)
                 | repeatUntil(thereIsNothingToParse)
    ;

    if (output_doc)
        parse(buffer, parameter.csv_separator);
    return output_doc;
}

}