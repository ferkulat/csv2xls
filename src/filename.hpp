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
#include <string>
namespace csv2xls
{
/**
 * \brief construct a file name for xls output
 * @param wish_name
 *
 * The name you wish to be the output file name. If it ends with `.xls` (case insensitive),
 * you will get the name like you suggested. If it ends with `.csv`, `csv`
 * gets replaced by `xls`. In all other cases the suggested name will extended with `.xls`.
 * @param count
 *
 * If `count` is > 0, the resulting file name will extended by the number `count` before `.xls`.
 * The number has 4 digits with leadung zeros.
 * @return
 *
 * The resulting file name.
 */
std::string
xls_filename( std::string wish_name,
              unsigned long count,   /** the number added to file name */
              unsigned long digits );/** minimum digits of the number  */
                        
} /* ----- end of namespace csv2xls ----- */
