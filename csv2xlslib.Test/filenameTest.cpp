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
        auto const actual = xls_filename("input.csv", 0, OutPutFileNameDigitCount(4));
        REQUIRE("input.xls"   == actual);
        REQUIRE("input.xls"   == xls_filename("input", 0, OutPutFileNameDigitCount(4)));
        REQUIRE("inp.xls"     == xls_filename("inp",   0, OutPutFileNameDigitCount(4)));
        REQUIRE("i.p0001.xls" == xls_filename("i.p",   1, OutPutFileNameDigitCount(4)));
    }
    SECTION("given second outfile adds numbering") {
        auto const actual = xls_filename("input", 1, OutPutFileNameDigitCount(4));
        REQUIRE("input0001.xls" == actual);
    }
    SECTION("given first outfile adds no numbering") {
        auto const actual = xls_filename("i.p", 0, OutPutFileNameDigitCount(4));
        REQUIRE("i.p.xls" == actual);
    }

}

TEST_CASE("with_xls_ending")
{
    REQUIRE("input.Xls"     == xls_filename("input.Xls", 0, OutPutFileNameDigitCount(4)));
    REQUIRE("input.xls"     == xls_filename("input.xls", 0, OutPutFileNameDigitCount(4)));
    REQUIRE("input0001.XLS" == xls_filename("input.XLS", 1, OutPutFileNameDigitCount(4)));
    REQUIRE("xls.xls"       == xls_filename("xls",       0, OutPutFileNameDigitCount(4)));
    REQUIRE("xls0001.xls"   == xls_filename("xls",       1, OutPutFileNameDigitCount(4)));
}

TEST_CASE("numbering")
{
    REQUIRE("input429496729.XLS"  ==  xls_filename("input.XLS", 429496729, OutPutFileNameDigitCount(4)));
    REQUIRE("input0429496729.XLS" == xls_filename("input.XLS", 429496729,  OutPutFileNameDigitCount(10)));
}

