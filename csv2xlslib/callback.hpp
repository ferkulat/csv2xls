/**
 * @file callback.hpp:
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

#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <stddef.h> // for type 'size_t'

namespace csv2xls
{
/**
 * \fn void csv_cb_end_of_field (void *s, size_t len, void *data)
 * \brief Call back function if csv parser reaches end of a field
 *
 * The csv parser sets the parameters.
 * @param s
 * Pointer to the string the parser read in the current field
 * @param len
 * Length of string `s`
 * @param data
 * A pointer to the data structure we registered during `csv_parse()`.
 */
void
csv_cb_end_of_field(void *s,
                    size_t len,
                    void *data);

/**
 * \fn void csv_cb_end_of_row (int c, void *data)
 *
 * \brief Call back function if csv parser reaches end of a row.
 *
 * The csv parser sets the parameters.
 * @param c
 * @param data
 * A pointer to the data structure we registered during `csv_parse()`.
 */
void
csv_cb_end_of_row(int c,
                  void *data);

/**
 * \fn void csv_cb_headline_field(void *s, size_t len, void *data)
 *
 * \brief Call back function if csv parser reaches end of a field in the head line
 *
 * The head line needs special handling. Additionaly to writng the field into
 * the xls file, we store it to reuse it later without parsing again.
 * The csv parser sets the parameters.
 * @param s
 * Pointer to the string the parser read in the current field
 * @param len
 * Length of string `s`
 * @param data
 * A pointer to a data structure we registered during `csv_parse()`.
 */
void
csv_cb_headline_field(  void *s,
                        size_t len,
                        void *data);
}/* ---- end of namespace csv2xls ---- */

#endif
