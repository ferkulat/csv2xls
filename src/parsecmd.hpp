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
#define PARSECMD_CPP
#include "version.h"
#include <string>
#include <limits.h>
#include "str2ulong.hpp"
namespace csv2xls
{
#define DEFAULT_XLS_MAX_LINES     65536
#define DEFAULT_CSV_TAB_DELIMITER 59 /** ';' */
#define DEFAULT_CSV_BUFFER_SIZE   1024*1024
#define MAX_CSV_BUFFER_SIZE       ULONG_MAX
#define XLS_DEF_DIGIT_COUNT       4
#define MAX_XLS_DIGIT_COUNT       10

/**
 */
typedef struct
{
  char          csv_tab_delimiter;
  std::string   csv_file_name;
  std::string   xls_file_name;
  bool          csv_file_has_headline;
  unsigned long xls_row_limit;
  std::string   xls_sheet_name;
  unsigned long input_buffer_size;
  unsigned long xls_digit_count;
}cmd_opts_t;
/**
 * \brief initialize the option struct with default values
 * @param opts
 * Reference to the option struct
 */
void
parsecmd_init(cmd_opts_t &opts);

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
int
parse_commandline(cmd_opts_t &opts,
                         int argc,
                        char **argv);

void
print_help(char*executable);
} /* ----- end of namespace csv2xls ----- */
#endif /*PARSECMD_HPP*/

