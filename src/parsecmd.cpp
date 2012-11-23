/*
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
#include <libgen.h>

namespace csv2xls
{
using namespace std;

void
parsecmd_init(cmd_opts_t &opts)
{
    opts.csv_file_has_headline  = false;
    opts.csv_tab_delimiter      = DEFAULT_CSV_TAB_DELIMITER;
    opts.xls_row_limit          = DEFAULT_XLS_MAX_LINES;
    opts.input_buffer_size      = DEFAULT_CSV_BUFFER_SIZE;
    opts.xls_digit_count        = XLS_DEF_DIGIT_COUNT;
}/* -----  end of function parsecmd_init  ----- */

void
print_version(char*executable)
{
    cout << executable << VERSION << endl;
}

void
print_help(char*executable)
{
    cout << "Usage: " << executable << " [options] file" << endl << endl
         << "Description: Read csv file and convert it to one or more excel files."
         << endl << endl;

    cout << "options:" << endl << endl;

    cout << "-b num"   << "\tset buffer size for parsing csv to num bytes." << endl
                       << "\tDefaults to " << DEFAULT_CSV_BUFFER_SIZE << "." << endl
                       << "\tMaximum value: " << MAX_CSV_BUFFER_SIZE << "."
                       << endl << endl;

    cout << "-d c"     << "\tset csv tab delimiter to c. Default: \'"
                       << (char)DEFAULT_CSV_TAB_DELIMITER << "\'" << endl << endl;

    cout << "-h"       << "\tPrint this help text and exit." << endl << endl;

    cout << "-H"       << "\tTake first line from csv file as head line for each"
                       << endl
                       << "\tproduced excel file. " << endl << endl;

    cout << "-l num"   << "\tbreak xls output into files with max num lines"
                       << endl
                       << "\tDefaults to " << DEFAULT_XLS_MAX_LINES << "." << endl
                       << "\tMaximum value: " << DEFAULT_XLS_MAX_LINES << "."
                       << "\tMinimum value: " << 2 << "."
                      << endl << endl;

    cout << "-o name"  << "\tSet output file name to \'name\'. If this option is"
                       << " not set," << endl
                       << "\ttake csv input file name and replace \'.csv\' with "
                       << "\'.xls\'." << endl
                       << "\tIf \'name\' does not end with \'.xls\', it will be "
                       << "added by program." << endl << endl;

    cout << "-w name"  << "\tSet the excel worksheet name to \'name\'. "
                       << "Defaults to \'Table 1\'" << endl << endl;

    cout << "-D num"   << "\tSet excel file name numbering to \'num\' digits "
                       << "with leading zeros." << endl
                       << "\tDefault: " << XLS_DEF_DIGIT_COUNT << "."
                       << " Maximum value: " << MAX_XLS_DIGIT_COUNT << "."
                       << endl << endl;
    cout << "-v"       << "\tPrint version and exit" << endl;


}/* -----  end of function print_help  ----- */


int
parse_commandline(cmd_opts_t &opts,int argc,char**argv)
{
    parsecmd_init(opts);
    //We need at least an input file
    if (argc < 2)
    {
        return 0;
    }
    optind = 0;
    int opt;
    int converted = 0 ;
    while ((opt = getopt(argc, argv, "b:d:hHl:o:w:D:v")) != -1)
    {

       switch (opt)
       {

           case 'b':
                    if (! str2ulong(optarg,
                                    opts.input_buffer_size,
                                    MAX_CSV_BUFFER_SIZE) )
                    {
                        return 0;
                    }
                    break;
           case 'd':
                    opts.csv_tab_delimiter = optarg[0];
                    break;
           case 'H':
                    opts.csv_file_has_headline = true;
                    break;
           case 'l':
                    converted = str2ulong(optarg,
                                    opts.xls_row_limit,
                                    DEFAULT_XLS_MAX_LINES);
                    if (    (!converted)
                          ||(opts.xls_row_limit < 2 ) )
                    {
                        return 0;
                    }
                    break;
           case 'o':
                    opts.xls_file_name.assign(optarg);
                    break;
           case 'w':
                    opts.xls_sheet_name.assign(optarg);
                    break;
           case 'D':
                    if (! str2ulong(optarg,
                                    opts.xls_digit_count,
                                    MAX_XLS_DIGIT_COUNT) )
                    {
                        return 0;
                    }
                    break;
           case 'v':
                    print_version(argv[0]);
                    exit(EXIT_SUCCESS);

           default: /* '?' */
               return 0;
       }
   }
   opts.csv_file_name.assign(argv[optind]);
   if (opts.xls_file_name.empty())
   {
       char *output_name = NULL;

       if (NULL != (output_name = basename(argv[optind])))
       {
           opts.xls_file_name.assign(output_name);
       }
       else
       {
           cerr << "Error determnining output file name" << endl;
           return 0;
       }
   }
   else
   {   /* If output file name ends with '\' or '/' it is a directory.
        * We construct output path from this directory and basename of input file
        */
       char lastchar = opts.xls_file_name[opts.xls_file_name.size()-1];
       if (    ( '/' == lastchar) /* *nix */
             ||('\\' == lastchar) /* windows */ )
       {
           opts.xls_file_name.append(basename(argv[optind]));
       }
   }
   return 1;
}/* -----  end of function parse_commandline  ----- */

}/* -----  end of namespace csv2xls  ----- */
