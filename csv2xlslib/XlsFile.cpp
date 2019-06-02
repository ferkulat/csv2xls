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
#include <iostream>
#include <algorithm>
namespace csv2xls
{

Row RowAfterNewSheet(xls_file_t& file)
{
    file.output_file_name.file_number++;
    return file.output_doc.RowAfterClearSheet(file.sheet_name);
}

Column appendCell(xls_file_t& file, CellContent cell_content)
{
    return file.output_doc.appendCell(cell_content);
}

bool isWithinRowLimit(xls_file_t const& file, Row row)
{
    return row.isLess(std::min(file.xls_row_limit, XLS_MAX_ROWS));
}

Row newLine(xls_file_t& file)
{
    auto const row = file.output_doc.newLine();

    if (isWithinRowLimit(file, row))
        return row;

    writeIntoFile(file);
    return RowAfterNewSheet(file);
}

void writeIntoFile(xls_file_t& file)
{
    file.output_doc.writeInto(file.output_file_name);
}




} // namespace csv2xls
