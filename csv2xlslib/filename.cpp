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
#include <regex>
namespace csv2xls
{

using namespace std;

    string ConvertCountToStringWithLeadingZero( unsigned long numberOfDigits,
                                                unsigned long count)
    {
        stringstream numstream;
        numstream.width(numberOfDigits);
        numstream.fill('0');
        numstream << count;
        return numstream.str();
    }

    struct FileNameParts{
        FileNameParts() = default;
        FileNameParts(std::string base, std::string type)
                :base(base), type(type){}
        std::string base;
        std::string type;
    };

    FileNameParts SplitIntoParts(std::string const& filename)
    {
        std::smatch file_type_match;
        if(std::regex_search(filename, file_type_match, std::regex(R"(\..{3}$)")))
        {
            return FileNameParts(file_type_match.prefix(), file_type_match[0]);
        }
        return FileNameParts(filename,"");
    }

    FileNameParts SetOutputFileNameParts(FileNameParts parts)
    {
        if (parts.type.empty()||
            std::regex_match(parts.type, std::regex(".csv", std::regex::icase)))
        {
            parts.type = ".xls";
        }
        else if(!std::regex_match(parts.type, std::regex(".xls", std::regex::icase)))
        {
            parts.base.append(parts.type);
            parts.type = ".xls";
        }
        return parts;
    }
    
    auto AddNumberToBaseName(unsigned long count, unsigned long digits)
    {
        return [count, digits](FileNameParts parts){
            if (count && digits)
                parts.base.append(ConvertCountToStringWithLeadingZero(digits, count));
            return parts;
        };
    }

    std::string BuildXlsFilename(FileNameParts parts)
    {
        return parts.base + parts.type;
    }

    string xls_filename(string wish_name,
                        unsigned long count,
                        unsigned long digits)
    {
        return BuildXlsFilename(
                AddNumberToBaseName(count, digits)(
                        SetOutputFileNameParts(
                                SplitIntoParts(wish_name))));
    }

}/*---namespace csv2xls---*/
