/*
 * @file str2ulong.hpp
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

#ifndef STR2ULONG_HPP
#define STR2ULONG_CPP
#include <limits.h>

namespace csv2xls
{


/**
 * \fn str2ulong
 * \brief converts string 'str' into unsigned long 'num'.
 * @param str
 * String to be converted
 * @param num
 * Where the result gets stored
 * @param max_value
 * The maximum allowed value for 'num'
 * @return
 * Returns 1 on success.
 * Returns 0 if:
 *      - conversion failed
 *      - conversion suceeded, but num is greater than max_value
 */

int
str2ulong(const char *str,
          unsigned long &num,
          unsigned long max_value);
} /* ----- end of namespace csv2xls ----- */
#endif /*STR2ULONG_HPP*/

