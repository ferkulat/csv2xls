//
// Created by marcel on 12/19/17.
//
/**
 * @file conversionTest.cpp
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
 * MA  02110-1301  USA *
 */

#include "../csv2xlslib/conversion.h"
#include "catch.hpp"
namespace conversionTest {

    TEST_CASE ("Converting a negative value to an unsigned type throws") {
        size_t size_t_value;
        REQUIRE_THROWS(size_t_value = ConvertTo<decltype(size_t_value)>(-4));
    }
    TEST_CASE ("Converting a posivite value of signed type to a too small unsigned type throws") {
        unsigned char unsigned_char;
        REQUIRE_THROWS(unsigned_char = ConvertTo<decltype(unsigned_char)>(256));
    }
    TEST_CASE ("Converting a negative value to a too small signed type throws") {
        char char_value;
        REQUIRE_THROWS(char_value = ConvertTo<decltype(char_value)>(-129));
    }
    TEST_CASE ("Converting a too big positive value of signed type to a too small signed type throws") {
        char char_value;
        REQUIRE_THROWS(char_value = ConvertTo<decltype(char_value)>(128));
    }
    TEST_CASE ("Converting unsigned into too small unsigned type throws") {
        unsigned char char_value;
        REQUIRE_THROWS(char_value = ConvertTo<decltype(char_value)>(256u));
    }
    TEST_CASE ("Converting too big unsigned into signed of same type size throws") {
        char char_value;
        REQUIRE_THROWS(char_value = ConvertTo<decltype(char_value)>((unsigned char)128));
    }
    TEST_CASE ("Converting too big unsigned into signed of smaller type size throws") {
        char char_value;
        REQUIRE_THROWS(char_value = ConvertTo<decltype(char_value)>((unsigned int)128));
    }
}