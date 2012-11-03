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

#include "filename.hpp"
#include <sstream>
#include <boost/algorithm/string.hpp>

namespace csv2xls
{

using namespace std;
using namespace boost;

#define FILE_TYPE_NAME_LENGHT 4
#define DIGIT_COUNT 4

typedef boost::find_iterator<std::string::iterator> string_find_iterator;


string 
xls_filename( string wish_name, 
              int count)
{
    string               basename;
    string               filetype;
    stringstream         ss;
    stringstream         numstream;
    string_find_iterator It;
    /*
     * separate base name from file type name, if possible 
     */
    if (iends_with(wish_name, ".xls")) 
    {
        /* devide wish_name into basename and file type name*/
      	basename.assign(wish_name.substr(0,(wish_name.size() - FILE_TYPE_NAME_LENGHT)));
      	It       = make_find_iterator( wish_name, 
                                       last_finder(".xls", is_iequal()) ); 
      	filetype = copy_range<std::string>(*It);
    }
    else if(iends_with(wish_name, ".csv"))
    {
        /* take base name and set file type name to '.xls'*/
        basename.assign(wish_name.substr(0,(wish_name.size() - FILE_TYPE_NAME_LENGHT)));
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
    ss << basename;
    if (count)
    {
        /*add count with DIGIT_COUNT digits width and leading zero to basename */
        numstream.width(DIGIT_COUNT);
        numstream.fill('0');
        numstream << count;
    	ss << numstream.str();
    }
    ss << filetype;
	
    return ss.str();   
}/* ----- end of funtcion xls_filename ----- */

}/*---namespace csv2xls---*/
