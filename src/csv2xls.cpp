/* *
 *
 * @file csv2xls.cpp:
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

#include "parsecmd.hpp"
#include "XlsFile.hpp"
#include "csv.hpp"
#include <errno.h>
#include "xls_workbook.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "readHeadLine.hpp"
#include "parseCsvFile.hpp"
using namespace csv2xls;




int
main(int argc, char *argv[])
{

    xls_file_t xls_out;
    csv_file_t csv_in;
    cmd_opts_t options;



    if (!parse_commandline(options, argc, argv))
    {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    xls_out.filename      = options.xls_file_name;
    xls_out.xls_row_limit = options.xls_row_limit;
    xls_out.sheet_name    = options.xls_sheet_name;
    xls_out.digit_count   = options.xls_digit_count;
    xls_out.wbook         = new xls_workbook();
    xls_out.page_number   = -1;
    xls_new_sheet(&xls_out);

    csv_in.tab_delimter = options.csv_tab_delimiter;
    csv_init_parser(csv_in);

    fstream csv_input(options.csv_file_name.c_str(),
                      ifstream::in|ifstream::binary);
    if ( !csv_input.is_open())
    {
        cerr << "Failed to open file " << options.csv_file_name << endl;
        exit(EXIT_FAILURE);
    }

    if (options.csv_file_has_headline)
    {
	readHeadLine(csv_input, csv_in, xls_out);
    }

    parseCsvFile(csv_input, csv_in, xls_out, options);

/**
 *  cleaning up memory and exit
 */
    csv_free(&csv_in.csv_file_parser);


    xls_dump_worksheet(&xls_out);
    delete(xls_out.wbook);
    csv_input.close();
    exit(EXIT_SUCCESS);
}/* ----- end of function main ----- */