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
#include "callback.hpp"
#include "memory.hpp"
#include <errno.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

    char_buf_t input_buffer;
    input_buffer.size = options.input_buffer_size;

    if ( !get_buffer(input_buffer))
    {
        cerr << "could not allocate " << options.input_buffer_size
             << " bytes of memory" << endl;
        exit(EXIT_FAILURE);
    }
    cerr << "allocated " << input_buffer.size << " bytes for input buffer" << endl;

    xls_out.filename      = options.xls_file_name;
    xls_out.xls_row_limit = options.xls_row_limit;
    xls_out.sheet_name    = options.xls_sheet_name;
    xls_out.page_number   = 0;
    xls_out.digit_count   = options.xls_digit_count;
    xls_init(&xls_out);


    csv_in.tab_delimter = options.csv_tab_delimiter;
    csv_init_parser(csv_in);

    fstream csv_input(options.csv_file_name.c_str(),
                      ifstream::in|ifstream::binary);
    if ( !csv_input.is_open())
    {
        cerr << "Failed to open file " << options.csv_file_name << endl;
        exit(EXIT_FAILURE);
    }
/*
 * If requested, treat the first line of input as head line for output.
 * When output gets split into several files, they start always with this line.
 */
    if (options.csv_file_has_headline)
    {
        string head_line_buffer;
        if(! getline(csv_input,head_line_buffer).fail())
        {
            //getline omits newline from input stream
            // but csv_parser needs it
            head_line_buffer.append("\n");

            if (csv_parse(&csv_in.csv_file_parser,
                          head_line_buffer.c_str(),
                          head_line_buffer.size(),
                          /* register call back function for end of csv field*/
                          csv_cb_headline_field,
                          /* register call back function for end of csv row*/
                          csv_cb_end_of_row,
                          /* to be passed to the call back functions*/
                          &xls_out
                         ) != head_line_buffer.size())
            {
                cerr << "Error while parsing file: %s" << endl
                     << csv_strerror(csv_error(&csv_in.csv_file_parser)) << endl;
            }
        }

    }


/**
 * read csv input lines and put it into xls file
 */
    unsigned long bytes_read;

    while(csv_input.good())
    {
        csv_input.read(input_buffer.mem, input_buffer.size);
        bytes_read = csv_input.gcount();

        if (csv_parse(&csv_in.csv_file_parser,
                      input_buffer.mem,
                      bytes_read,
                      /* register call back function for end of csv field*/
                      csv_cb_end_of_field,
                      /* register call back function for end of csv row*/
                      csv_cb_end_of_row,
                      /* to be passed to the call back functions*/
                      &xls_out
                     ) != bytes_read)
        {
            cerr << "Error while parsing file: %s" << endl
                 << csv_strerror(csv_error(&csv_in.csv_file_parser)) << endl;
        }

    }


/**
 *  cleaning up memory and exit
 */
    csv_free(&csv_in.csv_file_parser);


    xls_close(&xls_out);
    free(input_buffer.mem);
    exit(EXIT_SUCCESS);

}/* ----- end of function main ----- */


