//
// Created by marcel on 5/31/19.
//

#include "catch.hpp"
#include "readBuffer.h"
#include <algorithm>
namespace csv2xls
{

bool operator==(EndOfBuffer const& c1, EndOfBuffer const& c2)
{
    return (c1.unfinished_cell == c2.unfinished_cell);
}
bool operator==(EndOfLine const& c1, EndOfLine const& c2)
{
    return (c1.cell == c2.cell);
}
namespace ReadCellTest
{

template<size_t N>
Buffer createBufferFilledWith(char const (&content)[N], InputBufferSize input_buffer_size){
    auto buffer = Buffer(input_buffer_size);

    auto const count = std::min(static_cast<InputBufferSize::type>(N),input_buffer_size.Get());
    std::copy(std::cbegin(content), std::cbegin(content)+count, buffer.mem.get());

    return buffer;
}

TEST_CASE("Given a buffer containing a complete cell, returns Cell")
{
    auto buffer = createBufferFilledWith("cell1;cell2;cell", InputBufferSize(20));
    buffer.end  = buffer.mem.get() + 16;

    auto const actual   = std::get<CellContent>(read(buffer, CsvSeparator(';')));
    auto const expected = CellContent{buffer.mem.get(), 5};

    REQUIRE(actual == expected);

    REQUIRE(buffer.current_position == buffer.mem.get() + 6);
}

TEST_CASE("Given the last cell in buffer without new line returns EndOfBuffer with the cell fragment")
{
    auto buffer = createBufferFilledWith("cell1;cell2;cell", InputBufferSize(17));
    buffer.end  = buffer.mem.get()+16;
    buffer.current_position = buffer.mem.get() + 12;

    auto const actual   = std::get<EndOfBuffer>(read(buffer, CsvSeparator(';')));
    auto const expected = EndOfBuffer{CellContent{buffer.mem.get() + 12, 4}};

    REQUIRE(actual == expected);
}

TEST_CASE("Given the last cell in buffer with new line returns EndOfBuffer with the cell fragment")
{
    auto buffer             = createBufferFilledWith("cell1;cell2;cell\n", InputBufferSize(17));
    buffer.current_position = buffer.mem.get() + 12;

    auto const actual   = std::get<EndOfLine>(read(buffer, CsvSeparator(';')));
    auto const expected = EndOfLine{CellContent{buffer.mem.get() + 12, 4}};

    REQUIRE(actual == expected);
}

TEST_CASE(R"(Given the last cell in buffer with \r\n returns EndOfBuffer with the cell fragment)")
{
    auto buffer             = createBufferFilledWith("cell1;cell2;cell\r\n", InputBufferSize(18));
    buffer.current_position = buffer.mem.get() + 12;

    auto const actual   = std::get<EndOfLine>(read(buffer, CsvSeparator(';')));
    auto const expected = EndOfLine{CellContent{buffer.mem.get() + 12, 4}};

    REQUIRE(actual == expected);
}

TEST_CASE(R"(Given current position on buffer end returns EndOfBuffer without a cell fragment)")
{
    auto buffer = createBufferFilledWith("cell1;cell2;cell\r\n", InputBufferSize(18));
    buffer.end  = buffer.mem.get()+18;
    buffer.current_position = buffer.mem.get() + 18;

    auto const actual   = std::get<EndOfBuffer>(read(buffer, CsvSeparator(';')));
    auto const expected = EndOfBuffer{};

    REQUIRE(actual == expected);
}

TEST_CASE(R"(Quoted cell is allowed to contain the cell delimiter)")
{
    auto buffer             = createBufferFilledWith(R"(cell1;"cell2;hmm";cell\r\n)", InputBufferSize(25));
    buffer.current_position = buffer.mem.get() + 6;

    auto const actual   = std::get<CellContent>(read(buffer, CsvSeparator(';')));
    auto const expected = CellContent{buffer.mem.get() + 6, 11};

    REQUIRE(actual == expected);
}

TEST_CASE("Given a cell ending with \n, returns Cell, but the next read returns EndOfLine")
{
    auto buffer             = createBufferFilledWith("cell1;cell2\ncell", InputBufferSize(17));
    buffer.current_position = buffer.mem.get() + 6;

    auto const actual   = std::get<EndOfLine>(read(buffer, CsvSeparator(';')));
    auto const expected = EndOfLine{CellContent{buffer.mem.get() + 6, 5}};

    REQUIRE(actual == expected);
}

}
}