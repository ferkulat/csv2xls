#include "filenameTest.hpp"
#include <cppunit/config/SourcePrefix.h>
CPPUNIT_TEST_SUITE_REGISTRATION (filenameTest);

void filenameTest::setUp(){

}
void filenameTest::tearDown(){

}

void filenameTest::no_xls_ending(){
	CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.csv",0).compare("input.xls"));
	CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input",0    ).compare("input.xls"));
	CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input",1    ).compare("input0001.xls"));
	CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.xls",0).compare("input.xls"));
	CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.Xls",0).compare("input.Xls"));
	CPPUNIT_ASSERT (0 == csv2xls::xls_filename("input.XLS",1).compare("input0001.XLS"));
}


