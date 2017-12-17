/**
 * @file csv.hpp
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

#ifndef  CSV_HPP
#define  CSV_HPP

#include <csv.h>

namespace csv2xls
{

typedef struct
{
    struct csv_parser csv_file_parser; /** < the parser */
    char tab_delimter;
} csv_file_t;

/**
 * \brief hides some low lowlevel of libcsv
 *
 * @param parser
 */
void
csv_init_parser(csv_file_t &parser);

} /* ----- end of namesace csv2xls ----- */
#endif   /* ----- #ifndef CSV_HPP  ----- */
