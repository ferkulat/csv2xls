/**
 * @file XlsFile.hpp
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

#ifndef XLSFILE_HPP
#define XLSFILE_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include "workbook.hpp"

namespace xlslib_core
{
class workbook;
class worksheet;
}

namespace csv2xls
{
    constexpr unsigned long XLS_MAX_ROWS    = 65536;
    constexpr unsigned long XLS_MAX_COLUMNS = 256;
/**
 * \brief information about xls file to be passed to csv call back functions
 */
struct xls_file_t
{
    unsigned long current_column;
    unsigned long current_row;
    std::unique_ptr<workbook> wbook;
    long          page_number;
    unsigned long xls_row_limit;
    unsigned long digit_count;
    std::string sheet_name;
    std::string filename;
    std::vector<std::string> headline;
} ;

/**
 *
 * @param file
 */
void
xls_new_sheet(xls_file_t *file);


/**
 * \brief Write into the current xls data cell
 *
 *  adressed by `xlsfile->current_column`  and `xlsfile->current_row`.
 *  After writing increase `xlsfile->current_column` by 1.
 *
 * @param xlsfile
 * Pointer to the struct which holds the information of the xls data.
 * @param val
 * The string to be written into the current xls data cell.
 */
void
xls_append_cell(xls_file_t *xlsfile,
                std::string val);

/**
 * \brief Point to the next line at column 0 in xls data
 *
 * @param xlsfile
 * Pointer to the struct which holds the information of the xls data.
 */
void
xls_newline(xls_file_t *xlsfile);

/**
 * \fn void xls_dump_worksheet(xls_file_t * xlsfile)
 *
 * \brief Write xls data to disk an create a new workbook.
 *
 * This is where we make page breaks in xls data written to disk.
 * After that the `xlsfile->page_number` will be increased.
 * When option -H is set, every new workbook gets the head line in first row.
 * @param xlsfile
 * Pointer to the struct which holds the information of the xls data.
 */
void
xls_dump_worksheet(xls_file_t *xlsfile);

/**
 * \fn void xls_add_headline(xls_file_t*xlsfile)
 * \brief Add the head line to the xls data
 *
 * and make a new line after that. Ideally you should set
 * * `xlsfile->current_column = 0`  and
 * * `xlsfile->current_row = 0`
 *
 * before calling this function.
 * @param
 * xlsfile
 * Pointer to the struct which holds the information of the xls data.
 * @return
 * nix
 */
void
xls_add_headline(xls_file_t *xlsfile);

bool
xls_sheet_is_empty(xls_file_t *file);
} /* ----- end of namespace csv2xls ----- */
#endif /*end XLSFILE_HPP*/
