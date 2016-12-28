/**
 * @file memory.hpp
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

#ifndef MEMORY_HPP
#define MEMORY_HPP
/**
 *
 */
namespace csv2xls
{
/**
 * \brief structure to hold information about the allocated/ to be allocated memory
 */
typedef struct
{
	char *mem; /**< pointer to allocated memory*/
	unsigned long size; /**< number of bytes [to allocate|allocated]*/
} char_buf_t;

/**
 * \brief tries to allocate memory for char
 *
 * It tries to allocate buffer.size bytes for type `char`. if it failes,
 * it tries the half of the current requested amount.
 *
 * @param
 *  buffer is a reference to a struct char_buf_t. It holds informtion about
 *  the amount of memory to allocate.
 * @return
 * *On success:*
 *
 *  Returns 1. if succeeded to allocate at least 1 byte.
 *  `buffer.mem` holds the pointer to memory and
 *  buffer.size holds the count of bytes wich where allocated.
 *
 * *On failure:*
 *
 *  Returns 0.
 *  `buffer.mem` is set to NULL. `buffer.size` is 0.
 *
 */
int get_buffer(char_buf_t &buffer);

}/* ----- end of namespace csv2xls ----- */

#endif
