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


template<typename... Preds>
constexpr auto EitherOf(Preds... preds){
    return [preds...](auto const& callee) {
        auto const result = callee();
      return (... || preds(result));
    };
}

template<typename... Preds>
constexpr auto AllOf(Preds... preds){
    return [preds...](auto const& callee) {
      auto const result = callee();
      return (... && preds(result));
    };
}
}


namespace csv2xls
{
using chaining::operator|;
using chaining::repeatUntil;

namespace Domain
{

auto appendToOutputDoc(OutputDoc& output_doc, CsvType csv_type)
{
    using R = std::variant<Row, Column, EndOfBuffer>;
    return MatchType(csv_type
              , [&](CellContent cell) -> R { return output_doc.appendCell(cell); }
              , [&](EndOfLine       ) -> R { return output_doc.newLine(); }
              , [ ](EndOfBuffer eob ) -> R { return eob; }
              );
}

struct Ok{};
struct EndOfStream{};

auto fill(Buffer& buffer, std::istream& csv_input)
{
    auto const bytes_left        = buffer.current_position - buffer.mem.get();
    auto const max_bytes_to_read = ConvertTo<long>(buffer.m_size) - bytes_left;

    csv_input.read(buffer.current_position, max_bytes_to_read);

    buffer.end = buffer.current_position + csv_input.gcount();
    return csv_input.gcount();
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
    return [&]{
      return Domain::fill(buffer, csv_input);
    };
}
}

using ChainingAdaptors::appendToOutputDoc;
using ChainingAdaptors::fill;

auto isEndOfBuffer = [](EndOfBuffer){
    return true;
};

auto isRowLimit (OutputRowLimit output_row_limit)
{
    return [output_row_limit](Row row) {
        return row.isGreaterEqual(output_row_limit);
    };
}

template <typename... ARGS>
auto Condition(ARGS... args)
{
     return [args...](auto input){
         return  MatchType(input, args..., [](auto ){return false;});
     };
}


OutputDoc convertCsv(OutputDoc output_doc, Buffer& buffer, OutputRowLimit output_row_limit, std::istream& stream)
{
    auto readCellFrom = [&buffer]{ return read(buffer, CsvSeparator(';'));};

    auto myfun = readCellFrom
                    | appendToOutputDoc(output_doc)
                    | repeatUntil(Condition(isEndOfBuffer, isRowLimit(output_row_limit)))
                    ;

    while(stream.good() && Domain::fill(buffer, stream))
    {
        myfun()

            ;
    }
    return output_doc;

// jedes mal ein neues OutputDoc erzeugen?

}
}