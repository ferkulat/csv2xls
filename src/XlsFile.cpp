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
#include "xls_workbook.hpp"
#include "filename.hpp"
#include <iostream>
namespace csv2xls
{


void xls_new_sheet(xls_file_t *file)
{
    if (!file->sheet_name.empty())
    {
        file->wbook->clear_sheet(file->sheet_name);
    }
    else
    {
        file->wbook->clear_sheet("Table 1");
    }
    file->current_column = 0;
    file->current_row    = 0;
    xls_add_headline(file);
    file->page_number++;
}


void
xls_append_cell(xls_file_t *file,
                string label)
{
    //ignore columns > XLS_MAX_COLUMNS
    if (XLS_MAX_COLUMNS > file->current_column)
    {
        file->wbook->label(file->current_row,
                           file->current_column,
                           label);
        file->current_column++;
    }
}/* ----- end of function xls_append_cell ----- */

void
xls_newline(xls_file_t *file)
{
    file->current_column = 0;
    file->current_row++;
    if (   (file->current_row >= file->xls_row_limit)
         ||(file->current_row >= XLS_MAX_ROWS))
    {
        xls_dump_worksheet(file);
        xls_new_sheet(file);
    }
}/* ----- end of function xls_newline ----- */

void
xls_dump_worksheet(xls_file_t *file)
{
    if ( !xls_sheet_is_empty(file))
    {
        string fname = xls_filename(file->filename,
                                    file->page_number,
                                    file->digit_count);
        file->wbook->write_to_file(fname);
    }
}/* ----- end of function xls_dump_worksheet ----- */

void
xls_add_headline(xls_file_t *file)
{
    if (file->headline.size())
    {
              vector<string>::iterator it  = file->headline.begin();
        const vector<string>::iterator end = file->headline.end();
        for ( ; it != end; ++it )
        {
           xls_append_cell(file, *it);
        }
        xls_newline(file);
    }
}/* ----- end of function xls_add_headline ----- */

bool
xls_sheet_is_empty(xls_file_t *file)
{
    if (       (file->current_column == 0    )
            && (
                  (file->headline.size() && file->current_row == 1)
                ||(file->current_row == 0)
               )
       )
    {
        return true;
    }
    else
    {
        return false;
    }
}

}/* ---- end of namespace csv2xls ---- */
