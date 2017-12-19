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
#include <string>
#include <stdexcept>
#include "default_values.h"
namespace csv2xls
{

    typedef struct
    {
        std::string csv_file_name;
        std::string xls_file_name;
        std::string xls_sheet_name;
        unsigned long xls_row_limit     = DEFAULT_XLS_MAX_LINES;
        unsigned long input_buffer_size = DEFAULT_CSV_BUFFER_SIZE;
        unsigned long xls_digit_count   = DEFAULT_XLS_DIGIT_COUNT;
        char csv_tab_delimiter          = DEFAULT_CSV_TAB_DELIMITER;
        bool csv_file_has_headline      = false;
        bool exit_clean        = false;
    } opts_t;


     class BadCommandLineOption : public std::logic_error{
     public:
         BadCommandLineOption(char const *what);
     };

    opts_t
    checkOptions(opts_t opts);


    /**
     * \brief parse command line paramets and set the values of option struct
     * @param opts
     * Refeence to the options struct
     * @param argc
     * The  count of command  line parameters
     * @param argv
     * The char* array of commanad line
     * @return
     * Returns 1 if succeded. Otherwise 0.
     */
    opts_t
    parse_commandline(int argc,
                      char **argv);

    opts_t
    parsecmd_getopts(int argc,
                     char**argv);

    opts_t
    set_xls_filename(opts_t opts);
} /* ----- end of namespace csv2xls ----- */
#endif /*PARSECMD_HPP*/

