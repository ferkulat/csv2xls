//
// Created by marcel on 5/31/19.
//

#ifndef CSV2XLS_READBUFFER_H
#define CSV2XLS_READBUFFER_H
#include "csv2xls_types.h"
#include <memory>
#include <optional>
#include <variant>
namespace csv2xls{

struct Buffer
{
    explicit Buffer(size_t size_)
        :m_size(size_)
        ,mem(std::make_unique<char[]>(size_))
        ,end(mem.get())
        ,current_position(mem.get())
        {}
    size_t m_size;
    std::unique_ptr<char[]> mem;
    char const * end;
    char* current_position;
    char quoted = '\0';
};

struct EndOfLine{};
struct EndOfBuffer
{
    std::optional<CellContent> unfinished_cell;
};
using CsvType = std::variant<CellContent, EndOfLine, EndOfBuffer>;

CsvType read(Buffer& buffer, CsvSeparator csv_separator);
}
#endif // CSV2XLS_READBUFFER_H
