/**
 * @file callback.cpp:
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

#include "callback.hpp"
#include "XlsFile.hpp"
#include <csv.h>
namespace csv2xls
{

void csv_cb_end_of_field(void *s, size_t len, void *data)
{
    auto const* csv_field = static_cast<char const*>(s);
    auto &xls_file = *(xls_file_t*) data;

    appendCell(xls_file, CellContent(std::string(csv_field, len)));
}

void csv_cb_headline_field(void *s, size_t len, void *data)
{
    auto const* csv_field = static_cast<char const*>(s);
    auto &xls_file = *(xls_file_t*) data;

    if (XLS_MAX_COLUMNS.Get() >= xls_file.headline.size())
    {
        auto const& cell_content = xls_file.headline.emplace_back(std::string(csv_field, len));
        appendCell(xls_file, cell_content);
    }
}

void csv_cb_end_of_row(int , void *data)
{
    auto &xls_file = *(xls_file_t*) data;
    newLine(xls_file);
}

}/* ---- end of namespace csv2xls ---- */
