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
#include "memory.hpp"
#include <stdlib.h>

namespace csv2xls
{

int
get_buffer(char_buf_t &mem)
{
    mem.mem = NULL;
    unsigned long current_size = mem.size;
    /*
     * try to allocate mem.size bytes of memory from heap
     * if it does not work, try mem.size/2 bytes and so on
     * */
    while((current_size > 0)
            &&(NULL == mem.mem))
    {
        mem.mem = (char*) malloc(sizeof(char*)*current_size);
        if (NULL != mem.mem)
        {
            mem.size = current_size;
            return 1;
        }
        current_size = current_size/2;
    }
    mem.size = 0;
    return 0;
}/* ----- end of function get_buffer ----- */

}/* ----- end of namespace csv2xls ----- */
