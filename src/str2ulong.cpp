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

#include <stdlib.h>
#include <errno.h>
#include "str2ulong.hpp"
namespace csv2xls
{

int
str2ulong(const char *str,
          unsigned long &num,
          unsigned long max_value)
{
    char *endptr;
    errno = 0;
    num = strtoul(str, &endptr,10);
    if (   ((errno == ERANGE) && (num == ULONG_MAX ))
        || ((errno != 0     ) && (num == 0         ))  )
    {
       return 0;
    }

    if (endptr == str)/* no conversion is done*/
    {
       return 0;
    }

    if ( num > max_value )
    {
        return 0;
    }
    return 1;

}/* -----  end of function str2ulong  ----- */
}/* -----  end of namespace csv2xls  ----- */
