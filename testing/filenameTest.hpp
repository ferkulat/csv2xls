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
#ifndef FILENAME_TEST_H
#define FILENAME_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/filename.hpp"

using namespace std;

class filenameTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (filenameTest);

    CPPUNIT_TEST (no_xls_ending);
    CPPUNIT_TEST (with_xls_ending);
    CPPUNIT_TEST (numbering);

    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void no_xls_ending (void);
        void with_xls_ending (void);
        void numbering (void);
    private:
	string inputfilename;
};

#endif
