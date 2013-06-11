#include "str2ulongTest.hpp"
#include <cppunit/config/SourcePrefix.h>
CPPUNIT_TEST_SUITE_REGISTRATION (str2ulongTest);

void str2ulongTest::setUp(){}
void str2ulongTest::tearDown(){}

void str2ulongTest::fails_on_negative_value()
{
    inputstring.assign("-1");
    CPPUNIT_ASSERT (0 == csv2xls::str2ulong(inputstring.c_str(),num,10));
    CPPUNIT_ASSERT (0 == csv2xls::str2ulong(inputstring.c_str(),num,0));
}

void str2ulongTest::max_value()
{
    inputstring.assign("4294967296");
    CPPUNIT_ASSERT (0 == csv2xls::str2ulong(inputstring.c_str(),num,4294967295U));
    inputstring.assign("67296");
    CPPUNIT_ASSERT (0 == csv2xls::str2ulong(inputstring.c_str(),num,65536));
    CPPUNIT_ASSERT (1 == csv2xls::str2ulong(inputstring.c_str(),num,67296));
    CPPUNIT_ASSERT (67296 == num);
}


