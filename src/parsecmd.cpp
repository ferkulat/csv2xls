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
namespace csv2xls
{

using namespace std;
bool isDir(string path);
void csv_set_default_values(opts_t &opts)
{
	opts.csv_file_has_headline = false;
	opts.csv_tab_delimiter = DEFAULT_CSV_TAB_DELIMITER;
	opts.input_buffer_size = DEFAULT_CSV_BUFFER_SIZE;
}

void xls_set_default_values(opts_t &opts)
{
	opts.xls_row_limit = DEFAULT_XLS_MAX_LINES;
	opts.xls_digit_count = DEFAULT_XLS_DIGIT_COUNT;
}

void print_version()
{
	cout << PACKAGE_STRING << endl;
}

int setOptionsFromCmdLineArgs(opts_t &opts, cmd_opts_t &cmd_opts)
{
	csv_set_default_values(opts);
	xls_set_default_values(opts);
	opts.csv_file_name.assign(cmd_opts.csv_file_name);
	if (cmd_opts.input_buffer_size)
	{
		if (!str2ulong(cmd_opts.input_buffer_size, opts.input_buffer_size,
		MAX_CSV_BUFFER_SIZE))
		{
			cerr << "failed to get parameter for option 'b'" << endl;
			return 0;
		}
	}

	if (cmd_opts.csv_tab_delimiter)
		opts.csv_tab_delimiter = cmd_opts.csv_tab_delimiter[0];

	if (cmd_opts.csv_file_has_headline)
		opts.csv_file_has_headline = true;

	if (cmd_opts.xls_row_limit)
	{
		int converted = 0;
		converted = str2ulong(cmd_opts.xls_row_limit, opts.xls_row_limit,
		DEFAULT_XLS_MAX_LINES);
		if (!converted)
		{
			cerr << "failed to get parameter for option 'l'" << endl;
			return 0;
		}
		if ((opts.csv_file_has_headline) && (opts.xls_row_limit < 2))
		{
			cerr << "if first line is Head line, minimum line limit is 2"
					<< endl;
			return 0;
		}
		if ((!opts.csv_file_has_headline) && (opts.xls_row_limit < 1))
		{
			cerr << "minimum line limit is 1" << endl;
			return 0;
		}
	}

	if (cmd_opts.xls_file_name)
		opts.xls_file_name.assign(cmd_opts.xls_file_name);

	determine_xls_filename(opts);

	if (cmd_opts.xls_sheet_name)
		opts.xls_sheet_name.assign(cmd_opts.xls_sheet_name);
	else
		opts.xls_sheet_name.assign(DEFAULT_XLS_SHEET_NAME);

	if (cmd_opts.xls_digit_count)
	{
		if (!str2ulong(cmd_opts.xls_digit_count, opts.xls_digit_count,
		MAX_XLS_DIGIT_COUNT))
		{
			cerr << "failed to get parameter for option 'D'" << endl;
			return 0;
		}
	}
	return 1;
}

int parse_commandline(opts_t &opts, int argc, char**argv)
{
	int optind;
	cmd_opts_t cmd_opts;
	reset_cmd_opts(cmd_opts);
	csv_set_default_values(opts);
	xls_set_default_values(opts);
	//We need at least an input file
	if (argc < 2) return 0;

	if (!(optind = parsecmd_getopts(cmd_opts, argc, argv)))
		return 0;

	if (!setOptionsFromCmdLineArgs(opts, cmd_opts))
		return 0;

	return 1;
}/* -----  end of function parse_commandline  ----- */

int parsecmd_getopts(cmd_opts_t &cmd_opts, int argc, char**argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "b:d:hHl:o:w:D:v")) != -1)
	{

		switch (opt)
		{

		case 'b':
			cmd_opts.input_buffer_size = optarg;
			break;
		case 'd':
			cmd_opts.csv_tab_delimiter = optarg;
			break;
		case 'H':
			cmd_opts.csv_file_has_headline = true;
			break;
		case 'l':
			cmd_opts.xls_row_limit = optarg;
			break;
		case 'o':
			cmd_opts.xls_file_name = optarg;
			break;
		case 'w':
			cmd_opts.xls_sheet_name = optarg;
			break;
		case 'D':
			cmd_opts.xls_digit_count = optarg;
			break;
		case 'v':
			print_version();
			exit(EXIT_SUCCESS);

		default: /* '?' */
			return 0;
		}
	}
	cmd_opts.csv_file_name = argv[optind];

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

void reset_cmd_opts(cmd_opts_t &cmd_opts)
{
	cmd_opts.csv_file_has_headline = false;
	cmd_opts.csv_file_name = NULL;
	cmd_opts.csv_tab_delimiter = NULL;
	cmd_opts.input_buffer_size = NULL;
	cmd_opts.xls_digit_count = NULL;
	cmd_opts.xls_file_name = NULL;
	cmd_opts.xls_row_limit = NULL;
	cmd_opts.xls_sheet_name = NULL;
}
}/* -----  end of namespace csv2xls  ----- */
