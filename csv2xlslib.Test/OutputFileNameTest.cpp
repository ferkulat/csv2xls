/**
 * @file filenameTest.cpp
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
 * MA  02110-1301  USA *
 */

#include "catch.hpp"
#include <csv2xls_compound_types.h>

namespace csv2xls
{

TEST_CASE("numbering")
{
    OutputFileName output_file_name;
    output_file_name.name_no_extension = "input";
    output_file_name.extension = ".XLS";

    SECTION("Given a number with more than set in digit_count, there will be no leading zeros")
    {
        output_file_name.digit_count = DigitCount(4);

        REQUIRE("input429496729.XLS" == output_file_name.Get(FileNumber(429496729)));
    }

    SECTION("Given a number with less than set in digit_count, there will be leading zeros")
    {
        output_file_name.digit_count = DigitCount(10);

        REQUIRE("input0429496729.XLS" == output_file_name.Get(FileNumber(429496729)));
    }

    SECTION("Given a file number of 0, no number is added to the file name")
    {
        output_file_name.digit_count = DigitCount(10);
        REQUIRE("input.XLS" == output_file_name.Get(FileNumber(0)));
    }
}
}