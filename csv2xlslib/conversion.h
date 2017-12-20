/* *
 *
 * @file conversion.h:
 *
 * csv2xls - convert csv files into one or more Excel(TM) files
 * Copyright (C) 2017  Marcel Schneider
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

#ifndef CSV2XLS_CONVERSION_H
#define CSV2XLS_CONVERSION_H

#include <cstddef>
#include <ios>
#include <sstream>

class BadNumericConversion : public std::out_of_range
{
public:
    explicit BadNumericConversion(char const *what) : out_of_range(what){}
};

template<typename TargetType, typename SourceType>
TargetType ConvertTo(SourceType source)
{
    if constexpr (std::is_same<TargetType, SourceType>::value)
    {
        return source;
    }
    else if constexpr (!std::is_convertible<SourceType, TargetType>::value)
    {
        static_assert("types are not convertible");
    }
    if constexpr (std::is_signed<TargetType>::value ==
                  std::is_signed<SourceType>::value)
    {
         if constexpr (sizeof(TargetType) < sizeof(SourceType)) {
             if (source < SourceType(std::numeric_limits<TargetType>::min()))
             {
                 std::stringstream ss;
                 ss << "tried to assign too small negative value " << source;
                 throw BadNumericConversion(ss.str().c_str());
             }
             if (source > SourceType(std::numeric_limits<TargetType>::max()))
             {
                 std::stringstream ss;
                 ss << "tried to assign too big positive value " << source;
                 throw BadNumericConversion(ss.str().c_str());
             }
         }
    }
    if constexpr (std::is_unsigned<TargetType>::value &&
                  std::is_signed<SourceType>::value)
    {
        if (source < 0)
        {
            std::stringstream ss;
            ss << "tried to assign negative value " << source
               << "to unsigned type";
            throw BadNumericConversion(ss.str().c_str());
        }
        if constexpr (sizeof(TargetType) < sizeof(SourceType))
        {
            if(source > SourceType(std::numeric_limits<TargetType>::max()) )
            {
                std::stringstream ss;
                ss << "tried to assign a too big value " << source;
                throw BadNumericConversion(ss.str().c_str());

            }
        }
    }
    if constexpr (std::is_signed<TargetType>::value &&
                  std::is_unsigned<SourceType>::value)
    {
        if constexpr (sizeof(TargetType) <= sizeof(SourceType))
        {
            if (source > SourceType(std::numeric_limits<TargetType>::max()))
            {
                std::stringstream ss;
                ss << "tried to assign a too big value " << source;
                throw BadNumericConversion(ss.str().c_str());
            }
        }
    }
    return static_cast<TargetType>(source);
}
#endif //CSV2XLS_CONVERSION_H
