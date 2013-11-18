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

#include "filenameTest.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(Group1)
{
    void
    setUp(){}

    void
    tearDown(){}
};

TEST(Group1,no_xls_ending)
{
    STRCMP_EQUAL ("input.xls",    csv2xls::xls_filename("input.csv",0,4).c_str()  );
    STRCMP_EQUAL ("input.xls",    csv2xls::xls_filename("input",0,4    ).c_str()  );
    STRCMP_EQUAL ("input0001.xls",csv2xls::xls_filename("input",1,4    ).c_str()  );
}

TEST(Group1,with_xls_ending)
{
    STRCMP_EQUAL ("input.xls",    csv2xls::xls_filename("input.xls",0,4).c_str()  );
    STRCMP_EQUAL ("input.Xls",    csv2xls::xls_filename("input.Xls",0,4).c_str()  );
    STRCMP_EQUAL ("input0001.XLS",csv2xls::xls_filename("input.XLS",1,4).c_str()  );
}

TEST(Group1,numbering)
{
    STRCMP_EQUAL ("input4294967295.XLS", csv2xls::xls_filename("input.XLS",4294967295U,4).c_str()  );
    STRCMP_EQUAL ("input0429496729.XLS", csv2xls::xls_filename("input.XLS",429496729U,10).c_str()  );
}

