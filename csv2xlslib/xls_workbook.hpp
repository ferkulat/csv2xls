/**
 * @file xls_workbook.hpp
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
 * MA  02110-1301  USA *
 */

#include "csv2xls_types.h"
#include <filesystem>
#include <memory>
#include <string>
namespace csv2xls
{

class xls_workbook
{
public:
    xls_workbook();
    ~xls_workbook();
    xls_workbook(xls_workbook && workbook) = default;
    void clearSheet(XlsSheetName const& sheet_name);

    int writeInto(OutputFileName const& out_put_file);

    void setCell( Row row, Column column,
                  CellContent const& cell_content);
private:
    struct Impl;
    static void PimplDeleter(Impl*p);
    std::unique_ptr<Impl, void(*)(Impl*)>  pimpl;

};
}
