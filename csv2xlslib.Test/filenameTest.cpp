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

#include "../csv2xlslib/filename.hpp"
#include "catch.hpp"

using namespace csv2xls;


TEST_CASE("no_xls_ending")
{
    SECTION("given input.csv gives input.xls") {
        auto const actual = outputFilename(OutPutFileName("input.csv"), FileNumber(0), DigitCount(4));
        REQUIRE(OutPutFileName("input.xls"  ) == actual);
        REQUIRE(OutPutFileName("input.xls"  ) == outputFilename(OutPutFileName("input"), FileNumber(0), DigitCount(4)));
        REQUIRE(OutPutFileName("inp.xls"    ) == outputFilename(OutPutFileName("inp"),   FileNumber(0), DigitCount(4)));
        REQUIRE(OutPutFileName("i.p0001.xls") == outputFilename(OutPutFileName("i.p"),   FileNumber(1), DigitCount(4)));
    }
    SECTION("given second outfile adds numbering") {
        auto const actual = outputFilename(OutPutFileName("input"), FileNumber(1), DigitCount(4));
        REQUIRE(OutPutFileName("input0001.xls") == actual);
    }
    SECTION("given first outfile adds no numbering") {
        auto const actual = outputFilename(OutPutFileName("i.p"), FileNumber(0), DigitCount(4));
        REQUIRE(OutPutFileName("i.p.xls") == actual);
    }

}

TEST_CASE("with_xls_ending")
{
    REQUIRE(OutPutFileName("input.Xls"    ) == outputFilename(OutPutFileName("input.Xls"), FileNumber(0), DigitCount(4)));
    REQUIRE(OutPutFileName("input.xls"    ) == outputFilename(OutPutFileName("input.xls"), FileNumber(0), DigitCount(4)));
    REQUIRE(OutPutFileName("input0001.XLS") == outputFilename(OutPutFileName("input.XLS"), FileNumber(1), DigitCount(4)));
    REQUIRE(OutPutFileName("xls.xls"      ) == outputFilename(OutPutFileName("xls"),       FileNumber(0), DigitCount(4)));
    REQUIRE(OutPutFileName("xls0001.xls"  ) == outputFilename(OutPutFileName("xls"),       FileNumber(1), DigitCount(4)));
}

TEST_CASE("numbering")
{
    REQUIRE(OutPutFileName("input429496729.XLS" ) ==  outputFilename(OutPutFileName("input.XLS"), FileNumber(429496729), DigitCount(4)));
    REQUIRE(OutPutFileName("input0429496729.XLS") ==  outputFilename(OutPutFileName("input.XLS"), FileNumber(429496729),  DigitCount(10)));
}

