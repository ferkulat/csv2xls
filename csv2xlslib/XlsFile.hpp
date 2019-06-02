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

#include <vector>
#include <cstdint>
#include <memory>

#include "OutputDoc.hpp"
#include "csv2xls_types.h"

namespace csv2xls
{
    constexpr auto XLS_MAX_ROWS    = OutputRowLimit(65536);
    constexpr auto XLS_MAX_COLUMNS = OutputColumnLimit(256);
/**
 * \brief information about xls file to be passed to csv call back functions
 */
struct xls_file_t
{
    xls_file_t(OutputDoc output_doc_)
        : output_doc(std::move(output_doc_))
    {
    }

    OutputFileName output_file_name;
    OutputRowLimit xls_row_limit;
    OutputDoc      output_doc;
};

/**
 *
 * @param file
 */
Row
RowAfterNewSheet(xls_file_t& file);


/**
 * \brief Write into the current xls data cell
 *
 *  adressed by `xlsfile->current_column`  and `xlsfile->current_row`.
 *  After writing increase `xlsfile->current_column` by 1.
 *
 * @param xlsfile
 * Pointer to the struct which holds the information of the xls data.
 * @param cell_content
 * The string to be written into the current xls data cell.
 */
Column
appendCell(xls_file_t& xlsfile, CellContent cell_content);

/**
 * \brief Point to the next line at column 0 in xls data
 *
 * @param xlsfile
 * Pointer to the struct which holds the information of the xls data.
 */
Row newLine(xls_file_t& xlsfile);

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
writeIntoFile(xls_file_t& xlsfile);


} /* ----- end of namespace csv2xls ----- */
#endif /*end XLSFILE_HPP*/
