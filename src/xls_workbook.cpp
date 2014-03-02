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

#include "xls_workbook.hpp"
#include <xlslib.h>

namespace csv2xls
{

xls_workbook::xls_workbook()
{
	this->wbook = NULL;
	this->wsheet = NULL;
}

xls_workbook::~xls_workbook()
{
	delete (this->wbook);
	this->wbook = NULL;
}

void xls_workbook::clear_sheet(const std::string& sheetname)
{
	delete (this->wbook);
	this->wbook = NULL;
	this->wbook = new xlslib_core::workbook();
	this->wsheet = this->wbook->sheet(sheetname);
}

void xls_workbook::label(	unsigned32_t row,
							unsigned32_t col,
							const std::string& strlabel)
{
	this->wsheet->label(row, col, strlabel);
}

int xls_workbook::write_to_file(const std::string& file_name)
{
	return this->wbook->Dump(file_name);
}
}
