// Datei: str2ulongTest.hpp
#ifndef STR2ULONG_TEST_H
#define STR2ULONG_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/str2ulong.hpp"

using namespace std;

class str2ulongTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (str2ulongTest);

    CPPUNIT_TEST (negative_value);
    CPPUNIT_TEST (max_value);

    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void negative_value (void);
        void max_value (void);
    private:
	string inputstring;
	unsigned long num;
};

#endif
