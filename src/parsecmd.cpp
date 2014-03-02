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
#include "../config.h"
#include "filename.hpp"
#include "print_help.h"
#include <sstream>
namespace csv2xls
{

using namespace std;
bool isDir(string path);
void csv_set_default_values(opts_t &opts)
{
	opts.csv_file_has_headline = false;
	opts.csv_tab_delimiter = DEFAULT_CSV_TAB_DELIMITER;
	opts.input_buffer_size = DEFAULT_CSV_BUFFER_SIZE;
	opts.csv_file_name.clear();
}

void xls_set_default_values(opts_t &opts)
{
	opts.xls_row_limit = DEFAULT_XLS_MAX_LINES;
	opts.xls_digit_count = DEFAULT_XLS_DIGIT_COUNT;
	opts.xls_file_name.clear();
	opts.xls_sheet_name.clear();
}

void print_version()
{
	cout << PACKAGE_STRING << endl;
}

int checkOptions(opts_t &opts)
{
	if (0 == opts.input_buffer_size)
	{
		cerr << "failed to get parameter for option 'b'" << endl;
		return 0;
	}

	if (0 == opts.xls_row_limit)
	{
		cerr << "failed to get parameter for option 'l'" << endl;
		return 0;
	}else
	{
		if (DEFAULT_XLS_MAX_LINES < opts.xls_row_limit)
		{
			cerr << "DEFAULT_XLS_MAX_LINES is maximum value for option 'l'";
			cerr << endl;
			return 0;
		}
		if ((opts.csv_file_has_headline) && (opts.xls_row_limit < 2))
		{
			cerr << "if first line is head line, minimum line limit is 2";
			cerr << endl;
			return 0;
		}
	}

	determine_xls_filename(opts);

	if (opts.xls_sheet_name.empty())
		opts.xls_sheet_name.assign(DEFAULT_XLS_SHEET_NAME);

	if (MAX_XLS_DIGIT_COUNT < opts.xls_digit_count)
	{
		cerr << "failed to get parameter for option 'D'" << endl;
		return 0;
	}
	return 1;
}

int parse_commandline(opts_t &opts, int argc, char**argv)
{
	int optind;
	csv_set_default_values(opts);
	xls_set_default_values(opts);
	//We need at least an input file
	if (argc < 2) return 0;

	if (!(optind = parsecmd_getopts(opts, argc, argv)))
		return 0;

	if (!checkOptions(opts))
		return 0;

	return 1;
}/* -----  end of function parse_commandline  ----- */

int parsecmd_getopts(opts_t &opts, int argc, char**argv)
{
	csv_set_default_values(opts);
	xls_set_default_values(opts);
	int opt;
	while ((opt = getopt(argc, argv, "b:d:hHl:o:w:D:v")) != -1)
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
			print_version();
			exit(EXIT_SUCCESS);

		default: /* '?' */
			return 0;
		}
	}
	opts.csv_file_name = argv[optind];

	return optind;

}/* -----  end of function parsecmd_getopts  ----- */

int determine_xls_filename(opts_t &opts)
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
			cerr << "Error determining output file name" << endl;
			return 0;
		}
	}
	else
	{
		if (isDir(opts.xls_file_name))
			opts.xls_file_name.append(basename(inputname));
	}
	opts.xls_file_name = xls_filename(opts.xls_file_name, 0, 0);
	return 1;
}

bool isDir(string path)
{
	char lastchar = path[path.size() - 1];

	if (('/' == lastchar)	/* *nix */
	|| ('\\' == lastchar) )	/* windows */
		return 1;
	else
		return 0;
}

}/* -----  end of namespace csv2xls  ----- */
