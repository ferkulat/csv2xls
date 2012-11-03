#include "filenameTest.hpp"
#include <cppunit/config/SourcePrefix.h>
CPPUNIT_TEST_SUITE_REGISTRATION (filenameTest);

void 
filenameTest::setUp(){}

void 
filenameTest::tearDown(){}

void 
filenameTest::no_xls_ending()
{
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.csv",0,4).compare("input.xls"));
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input",0,4    ).compare("input.xls"));
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input",1,4    ).compare("input0001.xls"));
}
void 
filenameTest::with_xls_ending()
{
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.xls",0,4).compare("input.xls"));
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.Xls",0,4).compare("input.Xls"));
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.XLS",1,4).compare("input0001.XLS"));
}
void 
filenameTest::numbering()
{
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.XLS",4294967295U,4).compare("input4294967295.XLS"));
    CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.XLS",429496729U,10).compare("input0429496729.XLS"));
}

