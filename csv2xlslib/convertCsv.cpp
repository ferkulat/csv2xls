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
namespace chaining{

struct HigherOrderFunction{};
template<typename Predicate>
auto repeatWhile(Predicate predicate)
{
    return [predicate](auto callee){
        bool success = true;
        while(success)
        {
            success = predicate(callee());
        }
    };
}

template <typename Pred> struct repeatUntil : public HigherOrderFunction
{
    Pred m_pred;
    repeatUntil(Pred pred)
        : m_pred(pred)
    {
    }
    template <typename Callee> auto operator()(Callee callee) const
    {
        while (true)
        {
            auto const result = callee();
            if (m_pred(result))
                return result;
        }
    }
};

template<typename Callee, typename Caller>
auto operator|(Callee callee, Caller caller)
{
    if constexpr (std::is_base_of_v<HigherOrderFunction, Caller>)
    {
        return [callee, caller](){
          return caller(callee);
        };
    }
    else
    {
        return [callee, caller](auto const&... arg) { return caller(callee(arg...)); };
    }
}


}


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
using chaining::operator|;
using chaining::repeatUntil;

enum class ChainStatus{Break, Ok, EndOfStream};
namespace Domain
{

auto appendToOutputDoc(OutputDoc& output_doc, CsvType csv_type)
{
    using R = std::variant<Row, Column, EndOfBuffer, EndOfStream>;
    return MatchType(csv_type
              , [&](CellContent cell) -> R { return output_doc.appendCell(cell); }
              , [&](EndOfLine       ) -> R { return output_doc.newLine(); }
              , [ ](auto anything   ) -> R { return anything; }
              );
}


auto fill(Buffer& buffer, std::istream& csv_input)
{
    if (!csv_input.good())
        return false;

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
    return true;
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

}

namespace ChainingAdaptors
{
auto appendToOutputDoc(OutputDoc& output_doc)
{
    return [&output_doc](CsvType csv_type) {
        return Domain::appendToOutputDoc(output_doc, csv_type);
    };
}

auto fill(Buffer& buffer, std::istream& csv_input)
{
    return [&](ChainStatus status) {
        return (status == ChainStatus::Break)? ChainStatus::Break:
               (status == ChainStatus::EndOfStream)? ChainStatus::EndOfStream:
               (Domain::fill(buffer, csv_input)) ? ChainStatus::Ok : ChainStatus::EndOfStream;
    };
}

auto init (Buffer& buffer)
{
  return [&](std::variant<Row, Column, EndOfBuffer, EndOfStream> status){
      return MatchType(status
              ,[&](EndOfBuffer eob){Domain::init(buffer, eob);return ChainStatus::Ok;}
              ,[ ](EndOfStream    ){return ChainStatus::EndOfStream;}
              ,[ ](Row            ){return ChainStatus::Break;}
              ,[ ](auto           ){return ChainStatus::Ok;}
              );
  };
}

}

using ChainingAdaptors::appendToOutputDoc;
using ChainingAdaptors::fill;
using ChainingAdaptors::init;


auto isEndOfBuffer = [](EndOfBuffer){
  return true;
};
auto isEndOfStreamType = [](EndOfStream){
  return true;
};

auto isRowLimit (OutputRowLimit output_row_limit)
{
    return [output_row_limit](Row row) {
        return row.isGreaterEqual(output_row_limit);
    };
}

template <typename... ARGS>
auto matchesOneOf(ARGS... args)
{
     return [args...](auto input){
         return  MatchType(input, args..., [](auto ){return false;});
     };
}


OutputDoc convertCsv(OutputDoc output_doc, Buffer& buffer, OutputRowLimit output_row_limit, std::istream& stream)
{
    auto readCell = [&buffer]{ return read(buffer, CsvSeparator(';'));};

    ( readCell
        | appendToOutputDoc(output_doc)
        | repeatUntil(matchesOneOf(isEndOfBuffer, isEndOfStreamType, isRowLimit(output_row_limit)))
        | init(buffer)
        | fill(buffer, stream)
        | repeatUntil(isEitherOf(ChainStatus::Break, ChainStatus::EndOfStream))
    )();
    return output_doc;

// jedes mal ein neues OutputDoc erzeugen?

}
}