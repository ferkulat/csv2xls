//
// Created by marcel on 5/31/19.
//
#include "MatchVariantType.h"
#include "conversion.h"
#include "csv2xls_compound_types.h"
#include "readBuffer.h"
#include <Skills.h>
#include "convertCsv.h"
#include "funcomp.h"

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
        strncpy(buffer.current_position, cell.start, cell.length);
        buffer.end = buffer.current_position + cell.length;
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
            , [ ](EndOfStream eos ) -> R { return eos; }
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

auto isEndOfStream = [](EndOfStream){
    return true;
};

auto isRowLimit (std::optional<OutputRowLimit> output_row_limit)
{
    return [output_row_limit](Row row) {
        return (output_row_limit)? row.isGreaterEqual(output_row_limit.value()):false;
    };
}

OutputDoc convertCsv(Buffer& buffer, Parameter const& parameter, std::istream& stream, OutputDoc output_doc)
{
    auto appendTo = [&buffer, &stream](OutputDoc& output)
    {
        return ChainingAdaptors::appendTo(buffer, stream, output);
    };

    auto parse = read | appendTo(output_doc)
                      | repeatUntil(matchesOneOf(isEndOfStream,isRowLimit(parameter.output_row_limit)))
                      ;

    parse(buffer, parameter.csv_separator);
    return output_doc;
}
}