/**
 * @file xls_workbook.cpp
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

#include "XlsWorkBook.hpp"
#include <xlslib.h>
namespace csv2xls
{
struct XlsWorkBook::Impl{
    Impl(XlsSheetName const& xls_sheet_name_)
        : xls_sheet_name(xls_sheet_name_)
    {}
    std::unique_ptr<xlslib_core::workbook> wbook;
    xlslib_core::worksheet* wsheet;
    XlsSheetName xls_sheet_name;
};

void XlsWorkBook::clearSheet()
{
    this->pimpl->wbook  = std::make_unique<xlslib_core::workbook>();
    this->pimpl->wsheet = this->pimpl->wbook->sheet(pimpl->xls_sheet_name.Get());
}

void XlsWorkBook::setCell(Row row, Column column, CellContent cell_content)
{
    this->pimpl->wsheet->label(row.Get(), column.Get(), std::string(cell_content.start, cell_content.length));
}

int XlsWorkBook::writeInto(OutputFileName const& out_put_file)
{
    return this->pimpl->wbook->Dump(out_put_file.Get().string());
}
auto XlsWorkBook::columnLimit()-> std::optional<OutputColumnLimit>
{
    return OutputColumnLimit(256);
}
XlsWorkBook::XlsWorkBook(XlsSheetName const& xls_sheet_name)
    : pimpl(new Impl(xls_sheet_name), &PimplDeleter)
{
}

XlsWorkBook::~XlsWorkBook() {}
void XlsWorkBook::PimplDeleter(Impl* p)
{
    delete p;
}

}
