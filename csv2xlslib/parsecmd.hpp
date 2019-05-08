/*
 * @file parsecmd.hpp
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

#ifndef PARSECMD_HPP
#define PARSECMD_HPP
#include "csv2xls_compound_types.h"
#include "csv2xls_types.h"
#include "default_values.h"
#include <stdexcept>
#include <string>

namespace csv2xls
{

    class BadCommandLineOption : public std::logic_error
     {
     public:
         explicit BadCommandLineOption(std::string const& what);
     };

    struct Config
    {
        InputFile          csv_file_name;
        OutputFileName     output_file_name;
        XlsSheetName       xls_sheet_name        = XlsSheetName("Table1");
        OutputRowLimit     output_row_limit      = DEFAULT_XLS_MAX_LINES;
        InputBufferSize    input_buffer_size     = DEFAULT_CSV_BUFFER_SIZE;
        CsvSeparator       csv_separator         = DEFAULT_CSV_TAB_DELIMITER;
        InputHasHeadLine   csv_file_has_headline = InputHasHeadLine(false);
        bool exit_clean                          = false;
    };

    Config
    checkOptions(Config opts);


    Config
    parse_commandline(int argc,
                      char **argv);

    Config
    set_xls_filename(Config opts);
} /* ----- end of namespace csv2xls ----- */
#endif /*PARSECMD_HPP*/

