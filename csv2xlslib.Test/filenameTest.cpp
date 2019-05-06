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
        auto const actual = outputFilename(OutputFileName("input.csv"), FileNumber(0), DigitCount(4));
        REQUIRE(OutputFileName("input.xls"  ) == actual);
        REQUIRE(OutputFileName("input.xls"  ) == outputFilename(OutputFileName("input"), FileNumber(0), DigitCount(4)));
        REQUIRE(OutputFileName("inp.xls"    ) == outputFilename(OutputFileName("inp"),   FileNumber(0), DigitCount(4)));
        REQUIRE(OutputFileName("i.p0001.xls") == outputFilename(OutputFileName("i.p"),   FileNumber(1), DigitCount(4)));
    }
    SECTION("given second outfile adds numbering") {
        auto const actual = outputFilename(OutputFileName("input"), FileNumber(1), DigitCount(4));
        REQUIRE(OutputFileName("input0001.xls") == actual);
    }
    SECTION("given first outfile adds no numbering") {
        auto const actual = outputFilename(OutputFileName("i.p"), FileNumber(0), DigitCount(4));
        REQUIRE(OutputFileName("i.p.xls") == actual);
    }

}

TEST_CASE("with_xls_ending")
{
    REQUIRE(OutputFileName("input.Xls"    ) == outputFilename(OutputFileName("input.Xls"), FileNumber(0), DigitCount(4)));
    REQUIRE(OutputFileName("input.xls"    ) == outputFilename(OutputFileName("input.xls"), FileNumber(0), DigitCount(4)));
    REQUIRE(OutputFileName("input0001.XLS") == outputFilename(OutputFileName("input.XLS"), FileNumber(1), DigitCount(4)));
    REQUIRE(OutputFileName("xls.xls"      ) == outputFilename(OutputFileName("xls"),       FileNumber(0), DigitCount(4)));
    REQUIRE(OutputFileName("xls0001.xls"  ) == outputFilename(OutputFileName("xls"),       FileNumber(1), DigitCount(4)));
}

TEST_CASE("numbering")
{
    REQUIRE(OutputFileName("input429496729.XLS" ) ==  outputFilename(OutputFileName("input.XLS"), FileNumber(429496729), DigitCount(4)));
    REQUIRE(OutputFileName("input0429496729.XLS") ==  outputFilename(OutputFileName("input.XLS"), FileNumber(429496729),  DigitCount(10)));
}

