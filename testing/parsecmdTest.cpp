/**
 * @file parsecmdTest.cpp
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
#include "parsecmdTest.hpp"
#include <stdlib.h>
#include <string.h>
#include <wordexp.h>


#include <cppunit/config/SourcePrefix.h>
CPPUNIT_TEST_SUITE_REGISTRATION (parsecmdTest);




void
parsecmdTest::
print_argv(int count, char**argv)
{
    for(int i = 0; i < count; ++i)
    {
        cerr << argv[i] << " ";
    }
    cerr << endl;
}


void parsecmdTest::setUp()
{
}

void parsecmdTest::tearDown(){}

void parsecmdTest::no_options()
{
    wordexp_t args;
    wordexp("csv2xls input1.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input1.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input1.csv"));
    wordfree(&args);

    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    wordexp("csv2xls tmp/input2.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("tmp/input2.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input2.csv"));
    wordfree(&args);

    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    wordexp("csv2xls /tmp/input3.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("/tmp/input3.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input3.csv"));
    wordfree(&args);
}

void parsecmdTest::output_dir()
{
    wordexp_t args;
    wordexp("csv2xls  -o/tmp/ input.csv", &args,0);
    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    parse_commandline(opts,args.we_wordc,args.we_wordv);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("/tmp/input.csv"));
    wordfree(&args);

    wordexp("csv2xls  -o tmp/ input1.csv", &args,0);
    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    parse_commandline(opts,args.we_wordc,args.we_wordv);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input1.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("tmp/input1.csv"));
    wordfree(&args);
}

void parsecmdTest::line_limit_0()
{
    wordexp_t args;
    wordexp("csv2xls -l0 input.csv", &args,0);
    CPPUNIT_ASSERT (0 == parse_commandline(opts,args.we_wordc,args.we_wordv));
    wordfree(&args);
}

void
parsecmdTest::line_limit_1()
{
    wordexp_t args;
    wordexp("csv2xls -l1 input.csv", &args,0);
    CPPUNIT_ASSERT (0 == parse_commandline(opts,args.we_wordc,args.we_wordv));
    wordfree(&args);
}

void
parsecmdTest::line_limit_2()
{
    wordexp_t args;
    wordexp("csv2xls -l2 input.csv", &args,0);
    CPPUNIT_ASSERT (1 == parse_commandline(opts,args.we_wordc,args.we_wordv));
    wordfree(&args);
}


