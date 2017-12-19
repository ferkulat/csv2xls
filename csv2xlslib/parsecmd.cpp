/*
 * @file parsecmd.cpp
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
#include <unistd.h>     /* To parse command line options. */
#include <stdlib.h>
#include <iostream>
#include <strings.h>
#include <libgen.h>     /* basename() */
#include "version.h"
#include "filename.hpp"
#include "print_help.h"
#include <sstream>

namespace csv2xls
{

    using namespace std;
    bool isDir(string const& path);
    void print_version()
    {
        cout << gGIT_VERSION << endl;
    }

    opts_t checkOptions(opts_t opts)
    {
        if (0 == opts.input_buffer_size)
        {
            throw BadCommandLineOption( "failed to get parameter for option 'b'" );
        }

        if (0 == opts.xls_row_limit)
        {
            throw BadCommandLineOption("failed to get parameter for option 'l'" );
        }
        else
        {
            if (DEFAULT_XLS_MAX_LINES < opts.xls_row_limit)
            {
                throw BadCommandLineOption("DEFAULT_XLS_MAX_LINES is maximum value for option 'l'");
            }
            if ((opts.csv_file_has_headline) && (opts.xls_row_limit < 2))
            {
                throw BadCommandLineOption("if first line is head line, then minimum line limit is 2");
            }
        }

        if (opts.xls_sheet_name.empty())
            opts.xls_sheet_name.assign(DEFAULT_XLS_SHEET_NAME);

        if (MAX_XLS_DIGIT_COUNT < opts.xls_digit_count)
        {
            throw BadCommandLineOption("failed to get parameter for option 'D'");
        }
        return opts;
    }

    opts_t parse_commandline(int argc, char**argv)
    {
        //We need at least an input file
        if (argc < 2)
            throw BadCommandLineOption("too few arguments");

        return set_xls_filename(checkOptions(parsecmd_getopts(argc, argv)));

    }/* -----  end of function parse_commandline  ----- */

    opts_t parsecmd_getopts(int argc, char**argv)
    {
        opts_t opts;

        int opt;
        while ((opt = getopt(argc, argv, "b:d:thHl:o:w:D:v")) != -1)
        {
            stringstream ss;

            switch (opt)
            {
            case 'b':
                ss << optarg;
                ss >> opts.input_buffer_size;
                break;
            case 'd':
                opts.csv_tab_delimiter = optarg[0];
                break;
            case 't':
                opts.csv_tab_delimiter = CHAR_TABULATOR;
                break;
            case 'H':
                opts.csv_file_has_headline = true;
                break;
            case 'l':
                ss << optarg;
                ss >> opts.xls_row_limit;
                break;
            case 'o':
                opts.xls_file_name = optarg;
                break;
            case 'w':
                opts.xls_sheet_name = optarg;
                break;
            case 'D':
                ss << optarg;
                ss >> opts.xls_digit_count;
                break;
            case 'v':
                opts.exit_clean = true;
                print_version();
                break;
            case 'h':
                opts.exit_clean = true;
                print_help(argv[0]);
                break;
            default:
                throw BadCommandLineOption("");
            }
        }

        if (optind < argc)
        {
            opts.csv_file_name = argv[optind];
        }
        else
        {
            throw BadCommandLineOption("error: missing input file");
        }

        return opts;

    }/* -----  end of function parsecmd_getopts  ----- */

    opts_t set_xls_filename(opts_t opts)
    {
        string tmpstr;
        tmpstr.assign(opts.csv_file_name);
        char *inputname = (char*) tmpstr.c_str();

        if (opts.xls_file_name.empty())
        {
            char *output_name = NULL;
            if (NULL != (output_name = basename(inputname)))
            {
                opts.xls_file_name.assign(output_name);
            }
            else
            {
                throw BadCommandLineOption("Error determining output file name");
            }
        }
        else
        {
            if (isDir(opts.xls_file_name))
                opts.xls_file_name.append(basename(inputname));
        }
        opts.xls_file_name = xls_filename(opts.xls_file_name, 0, 0);
        return opts;
    }

    bool isDir(string const& path)
    {
        char lastchar = path[path.size() - 1];

        if (('/' == lastchar) /* *nix */
        || ('\\' == lastchar)) /* windows */
            return true;
        else
            return false;
    }

    BadCommandLineOption::BadCommandLineOption(char const * what)
            : logic_error(what) {}
}/* -----  end of namespace csv2xls  ----- */
