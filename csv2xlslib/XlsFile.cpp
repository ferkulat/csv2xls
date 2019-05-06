/*
 * @file XlsFile.cpp
 *
 * csv2xls - convert csv files into one or more Excel(TM) files
 * Copyright (C) 2012  Marcel Schneider
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU GENERAL PUBLIC LICENSE
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU GENERAL PUBLIC LICENSE for more details.
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 *
 * Free Software Foundation Inc.
 * 51 Franklin Street
 * Fifth Floor
 * Boston
 * MA  02110-1301  USA
 */
#include "XlsFile.hpp"
#include "filename.hpp"
#include <iostream>
#include <algorithm>
namespace csv2xls
{

void newSheet(xls_file_t& file)
{
    file.output_doc.clearSheet(file.sheet_name);
    file.current_column = Column(0);
    file.current_row    = Row(0);
    addHeadline(file);
    file.file_number++;
}

void appendCell(xls_file_t& file, CellContent const& cell_content)
{
    // ignore columns > XLS_MAX_COLUMNS
    if (file.current_column.isGreaterEqual(XLS_MAX_COLUMNS))
        return;

    file.output_doc.setCell(file.current_row, file.current_column, cell_content);
    file.current_column++;
}

bool isWithinRowLimit(xls_file_t const& file)
{
    return file.current_row.isLess(std::min(file.xls_row_limit, XLS_MAX_ROWS));
}

void newLine(xls_file_t& file)
{
    file.current_column = Column(0);
    file.current_row++;

    if (isWithinRowLimit(file))
        return;

    writeIntoFile(file);
    newSheet(file);
}

void writeIntoFile(xls_file_t& file)
{
    if (isEmptySheet(file))
        return;

    auto fname = outputFilename(file.output_file_name, file.file_number, file.digit_count);
    file.output_doc.writeInto(fname);
}

void addHeadline(xls_file_t& file)
{
    if (file.headline.empty())
        return;

    for (auto const& column_name : file.headline)
        appendCell(file, column_name);

    newLine(file);
}

bool isAtFirstRow(xls_file_t const& file)
{
    auto const first_row = (file.headline.empty()) ? Row(0) : Row(1);
    return (first_row == file.current_row);
}

bool isAtFirstColumn(xls_file_t const& file)
{
    return (Column(0) == file.current_column);
}

bool isEmptySheet(xls_file_t const& file)
{
    return (isAtFirstColumn(file) && isAtFirstRow(file));
}

} // namespace csv2xls
