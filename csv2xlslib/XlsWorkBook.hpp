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

#include "csv2xls_compound_types.h"
#include "csv2xls_types.h"
#include <memory>
#include <string>
namespace csv2xls
{

class XlsWorkBook
{
public:
    XlsWorkBook(XlsSheetName const& xls_sheet_name);
    ~XlsWorkBook();
    XlsWorkBook(XlsWorkBook && workbook);

    int writeInto(OutputFileName const& output_file_name, FileNumber file_number)const;

    void setCell( Row row, Column column,
                  CellContent cell_content);
    auto columnLimit()-> std::optional<OutputColumnLimit>;
private:
    void clearSheet();
    struct Impl;
    std::unique_ptr<Impl>  pimpl;

};
}
