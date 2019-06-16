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
using funcomp::Do;


enum class Status{Break, Ok, EndOfStream};
namespace Domain
{

auto appendToOutputDoc(OutputDoc& output_doc, CsvType csv_type)
{
    using R = std::variant<Row, Column, EndOfBuffer, EndOfStream>;
    return MatchType(csv_type
              , [&](CellContent cell) -> R { return output_doc.appendCell(cell); }
              , [&](EndOfLine   eol ) -> R { output_doc.appendCell(eol.cell);return output_doc.newLine(); }
              , [ ](auto anything   ) -> R { return anything; }
              );
}


auto fill(Buffer& buffer, std::istream& csv_input)
{
    if (!csv_input.good())
        return Status::EndOfStream;

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
    return Status::Ok;
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
    return Status::Ok;
}

}

namespace ChainingAdaptors
{
auto appendTo(OutputDoc& output_doc)
{
    return [&output_doc](CsvType csv_type) {
        return Domain::appendToOutputDoc(output_doc, csv_type);
    };
}

auto fill(Buffer& buffer, std::istream& csv_input)
{
    return [&](Status ) {
        return  Domain::fill(buffer, csv_input);
    };
}

auto init (Buffer& buffer)
{
  return [&](std::variant<Row, Column, EndOfBuffer, EndOfStream> status){
      return MatchType(status
              ,[&](EndOfBuffer eob){return Domain::init(buffer, eob);}
              ,[ ](EndOfStream    ){return Status::EndOfStream;}
              ,[ ](Row            ){return Status::Break;}
              ,[ ](auto           ){return Status::Ok;}
              );
  };
}

}

using ChainingAdaptors::appendTo;
using ChainingAdaptors::fill;
using ChainingAdaptors::init;

auto isEndOfBuffer = [](EndOfBuffer){
  return true;
};
auto isEndOfStream = [](EndOfStream){
  return true;
};

auto isRowLimit (std::optional<OutputRowLimit> output_row_limit)
{
    return [output_row_limit](Row row) {
        return (output_row_limit)? row.isGreaterEqual(output_row_limit.value()):false;
    };
}
auto isOk = [](Status status){return status == Status::Ok;};
template <typename... ARGS>
auto matchesOneOf(ARGS... args)
{
     return [args...](auto input){
         return  MatchType(input, args..., [](auto ){return false;});
     };
}


OutputDoc convertCsv(OutputDoc output_doc, Buffer& buffer, Parameter const& parameter, std::istream& stream)
{
    auto const noCells  = matchesOneOf(isEndOfBuffer, isEndOfStream, isRowLimit(parameter.output_row_limit));

    auto myfun = read
                    | appendTo(output_doc)
                    | repeatUntil(noCells)
                    | init(buffer)
                    | Do(fill(buffer, stream)).If(isOk)
                    | repeatUntil(isEitherOf(Status::Break, Status::EndOfStream))
                    ;

    myfun(buffer, parameter.csv_separator);
    return output_doc;

// jedes mal ein neues OutputDoc erzeugen?

}
}