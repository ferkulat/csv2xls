// Datei: filenameTest.hpp
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
