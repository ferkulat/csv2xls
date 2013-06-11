/**
 * @file parsecmdTest.hpp
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
// Datei: parsecmdTest.hpp
#ifndef PARSECMD_TEST_H
#define PARSECMD_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/parsecmd.hpp"
#include <wordexp.h>

using namespace std;
using namespace csv2xls;
class parsecmdTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (parsecmdTest);

    CPPUNIT_TEST (no_options);
    CPPUNIT_TEST (no_options_subdir);
    CPPUNIT_TEST (no_options_absolute_path);
    CPPUNIT_TEST (output_dir_absolute);
    CPPUNIT_TEST (output_dir_relative);
    CPPUNIT_TEST (line_limit_0);
    CPPUNIT_TEST (line_limit_1);
    CPPUNIT_TEST (line_limit_2);

    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void no_options (void);
        void no_options_subdir (void);
        void no_options_absolute_path(void);
        void output_dir_absolute(void);
        void output_dir_relative(void);
        void line_limit_0 (void);
        void line_limit_1 (void);
        void line_limit_2 (void);
    private:
	cmd_opts_t opts;
        void print_argv(int ,char**);
        wordexp_t args;
};

#endif
