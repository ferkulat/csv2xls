/*
 * @file filename.cpp
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

#include "filename.hpp"
#include <sstream>
#include <algorithm>

namespace csv2xls
{

using namespace std;

constexpr size_t FILE_TYPE_NAME_LENGTH = 4;

string ConvertCountToStringWithLeadingZero(	unsigned long numberOfDigits,
                                            unsigned long count)
{
    stringstream numstream;
    numstream.width(numberOfDigits);
    numstream.fill('0');
    numstream << count;
    return numstream.str();
}

string xls_filename(string wish_name,
                    unsigned long count,
                    unsigned long digits)
{
    string tmp_name;
    string tmp_type;
    string basename;
    string filetype;
    int basename_length;

    if (4 > wish_name.size())
    {
        wish_name.append(".xls");
    }
    basename_length = wish_name.size() - FILE_TYPE_NAME_LENGTH;

    /**
     * make comparisons case insensitive
     */
    tmp_name.assign(wish_name);
    std::transform(tmp_name.begin(), tmp_name.end(), tmp_name.begin(),
            ::tolower);

    tmp_type.assign(tmp_name.substr(basename_length, FILE_TYPE_NAME_LENGTH));

    /*
     * separate base name from file type name, if possible
     */
    if (0 == tmp_type.compare(".xls"))
    {
        /* devide wish_name into basename and file type name*/
        basename.assign(wish_name.substr(0, basename_length));
        filetype.assign(
                wish_name.substr(basename_length, FILE_TYPE_NAME_LENGTH));
    }
    else if (0 == tmp_type.compare(".csv"))
    {
        /* take base name and set file type name to '.xls'*/
        basename.assign(wish_name.substr(0, basename_length));
        filetype.assign(".xls");
    }
    else
    {
        /* take whole wish name for basename and set file type name to 'xls'. */
        basename.assign(wish_name);
        filetype.assign(".xls");
    }

    /*
     * Construct the file name from base name , number and file type name
     */
    if (count)
        basename.append(ConvertCountToStringWithLeadingZero(digits, count));
    basename.append(filetype);

    return basename;
}/* ----- end of function xls_filename ----- */

}/*---namespace csv2xls---*/
