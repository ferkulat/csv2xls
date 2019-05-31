//
// Created by marcel on 5/31/19.
//
#include "readBuffer.h"
namespace csv2xls
{
size_t cellLengthForLineEnd(char const* const start, char const* const current_position)
{
    auto const length1 = current_position - start;
    if ((length1) && (*(current_position - 1) == '\r'))
    {
        return static_cast<size_t>(length1 - 1);
    }
    return static_cast<size_t>(length1);
}
CsvType read(Buffer& buffer, CsvSeparator csv_separator)
{
    auto*       current_position = buffer.current_position;
    auto* const start            = buffer.current_position;

    while ((current_position != buffer.end))
    {
        if (buffer.quoted == '\0')
        {
            if (*current_position == csv_separator.Get())
            {
                buffer.current_position = current_position + 1;
                return CellContent{start, static_cast<size_t>(current_position - start)};
            }
            if (*current_position == '\n')
            {
                auto const length = cellLengthForLineEnd(start, current_position);
                if (length)
                {
                    buffer.current_position = current_position;
                    return CellContent{start, length};
                }
                buffer.current_position = current_position + 1;
                return EndOfLine{};
            }
            if (*current_position == '"')
            {
                buffer.quoted = '"';
            }
        }
        else if (buffer.quoted == '"')
        {
            if (*current_position == '"')
            {
                buffer.quoted = '\0';
            }
        }
        ++current_position;
    }
    buffer.current_position = current_position;
    auto const length       = static_cast<size_t>(current_position - start);
    return (length) ? EndOfBuffer{CellContent{start, length}} : EndOfBuffer{};
}
}