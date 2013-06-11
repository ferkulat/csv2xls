/**
 * @file TestMain.cpp
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

/*** testMain.cpp ***/
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

int main (int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS :: TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS :: TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS :: BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS :: TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS :: TestFactoryRegistry :: getRegistry ().makeTest ());
    testrunner.run (testresult);

    // output results in compiler-format
    CPPUNIT_NS :: CompilerOutputter compileroutputter (&collectedresults, std::cerr);
    compileroutputter.write ();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful () ? 0 : 1;
}
