//
// Created by marcel on 5/31/19.
//
#include "MatchVariantType.h"
#include "XlsFile.hpp"
#include "conversion.h"
#include "csv2xls_compound_types.h"
#include "readBuffer.h"
#include <Skills.h>
#include "convertCsv.h"
#include "funcomp.h"

namespace csv2xls
{
template<typename... Preds>
constexpr auto EitherOf(Preds... preds){
    return [preds...](auto const& value) {
      return (... || preds(value));
    };
}


template<typename... T>
constexpr auto isEitherOf(T... t){
    return [t...](auto const& value) {
      return (... || (t == value));
    };
}

template<typename... Preds>
constexpr auto AllOf(Preds... preds){
    return [preds...](auto const& value) {
      return (... && preds(value));
    };
}


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
    auto const bytes_to_read = ConvertTo<long>(buffer.m_size) - bytes_left;

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

    auto init(Buffer& buffer, EndOfBuffer eob)
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
    }

    auto appendToOutputDoc(Buffer& buffer, std::istream& csv_input, OutputDoc& output_doc, CsvType csv_type)
    {
        using R = ParseResult;
        return MatchType(csv_type
                , [&](CellContent cell) -> R { output_doc.appendCell(cell); return Ok{}; }
                , [&](EndOfLine   eol ) -> R { output_doc.appendCell(eol.cell);return output_doc.newLine(); }
                , [&](EndOfBuffer eob ) -> R { init(buffer, eob); return fill(buffer, csv_input);}
                , [ ](EndOfStream eos ) -> R { return eos; }
        );
    }

}

namespace ChainingAdaptors
{
auto appendTo(Buffer& buffer, std::istream& csv_input, OutputDoc& output_doc)
{
    return [&](CsvType csv_type) {
        return Domain::appendToOutputDoc(buffer, csv_input, output_doc, csv_type);
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
template <typename... ARGS>
auto matchesOneOf(ARGS... args)
{
     return [args...](auto input){
         return  MatchType(input, args..., [](auto ){return false;});
     };
}


OutputDoc convertCsv(OutputDoc output_doc, Buffer& buffer, Parameter const& parameter, std::istream& stream)
{
    auto appendTo = [&buffer, &stream](OutputDoc& output)
    {
        return ChainingAdaptors::appendTo(buffer, stream, output);
    };

    auto myfun = read
                    | appendTo(output_doc)
                    | repeatUntil(matchesOneOf(isEndOfStream,isRowLimit(parameter.output_row_limit)))
                    ;

    myfun(buffer, parameter.csv_separator);
    return output_doc;

// jedes mal ein neues OutputDoc erzeugen?

}
}