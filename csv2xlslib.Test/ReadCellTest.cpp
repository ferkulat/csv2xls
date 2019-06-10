//
// Created by marcel on 5/31/19.
//

#include "catch.hpp"
#include "readBuffer.h"
#include <string.h>
namespace csv2xls
{
bool operator==(CellContent const& c1, CellContent const& c2)
{
    return (c1.start == c2.start) && (c1.length == c2.length);
}

bool operator==(EndOfBuffer const& c1, EndOfBuffer const& c2)
{
    return (c1.unfinished_cell == c2.unfinished_cell);
}
namespace ReadCellTest
{

TEST_CASE("Given a buffer containing a complete cell, returns Cell")
{
    auto       buffer  = Buffer(20);
    auto const content = "cell1;cell2;cell";
    buffer.end         = buffer.mem.get() + 16;
    strncpy(buffer.mem.get(), content, buffer.m_size);

    auto const actual   = std::get<CellContent>(read(buffer, CsvSeparator(';')));
    auto const expected = CellContent{buffer.mem.get(), 5};

    REQUIRE(actual == expected);

    REQUIRE(buffer.current_position == buffer.mem.get() + 6);
}

TEST_CASE("Given the last cell in buffer without new line returns EndOfBuffer with the cell fragment")
{
    auto       buffer       = Buffer(16);
    auto const content      = "cell1;cell2;cell";
    buffer.end = buffer.mem.get()+16;
    buffer.current_position = buffer.mem.get() + 12;

    strncpy(buffer.mem.get(), content, buffer.m_size);

    auto const actual   = std::get<EndOfBuffer>(read(buffer, CsvSeparator(';')));
    auto const expected = EndOfBuffer{CellContent{buffer.mem.get() + 12, 4}};

    REQUIRE(actual == expected);
}

TEST_CASE("Given the last cell in buffer with new line returns EndOfBuffer with the cell fragment")
{
    auto       buffer       = Buffer(17);
    auto const content      = "cell1;cell2;cell\n";
    buffer.current_position = buffer.mem.get() + 12;

    strncpy(buffer.mem.get(), content, buffer.m_size);

    auto const actual   = std::get<CellContent>(read(buffer, CsvSeparator(';')));
    auto const expected = CellContent{buffer.mem.get() + 12, 4};

    REQUIRE(actual == expected);
}

TEST_CASE(R"(Given the last cell in buffer with \r\n returns EndOfBuffer with the cell fragment)")
{
    auto       buffer       = Buffer(18);
    auto const content      = "cell1;cell2;cell\r\n";
    buffer.current_position = buffer.mem.get() + 12;

    strncpy(buffer.mem.get(), content, buffer.m_size);

    auto const actual   = std::get<CellContent>(read(buffer, CsvSeparator(';')));
    auto const expected = CellContent{buffer.mem.get() + 12, 4};

    REQUIRE(actual == expected);
}

TEST_CASE(R"(Given current position on buffer end returns EndOfBuffer without a cell fragment)")
{
    auto       buffer       = Buffer(18);
    auto const content      = "cell1;cell2;cell\r\n";
    buffer.end = buffer.mem.get()+18;
    buffer.current_position = buffer.mem.get() + 18;

    strncpy(buffer.mem.get(), content, buffer.m_size);

    auto const actual   = std::get<EndOfBuffer>(read(buffer, CsvSeparator(';')));
    auto const expected = EndOfBuffer{};

    REQUIRE(actual == expected);
}

TEST_CASE(R"(Quoted cell is allowed to contain the cell delimiter)")
{
    auto       buffer       = Buffer(25);
    auto const content      = R"(cell1;"cell2;hmm";cell\r\n)";
    buffer.current_position = buffer.mem.get() + 6;

    strncpy(buffer.mem.get(), content, buffer.m_size);

    auto const actual   = std::get<CellContent>(read(buffer, CsvSeparator(';')));
    auto const expected = CellContent{buffer.mem.get() + 6, 11};

    REQUIRE(actual == expected);
}

TEST_CASE("Given a cell ending with \n, returns Cell, but the next read returns EndOfLine")
{
    auto       buffer       = Buffer(17);
    auto const content      = "cell1;cell2\ncell";
    buffer.current_position = buffer.mem.get() + 6;

    strncpy(buffer.mem.get(), content, buffer.m_size);

    {
        auto const actual   = std::get<CellContent>(read(buffer, CsvSeparator(';')));
        auto const expected = CellContent{buffer.mem.get() + 6, 5};

        REQUIRE(actual == expected);
    }
    {
        auto const actual = read(buffer, CsvSeparator(';'));

        REQUIRE(std::holds_alternative<EndOfLine>(actual));
    }
}

}
}