// Datei: parsecmdTest.hpp
#ifndef PARSECMD_TEST_H
#define PARSECMD_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/parsecmd.hpp"

using namespace std;
using namespace csv2xls;
class parsecmdTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (parsecmdTest);

    CPPUNIT_TEST (no_options);
//    CPPUNIT_TEST (with_xls_ending);

    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void no_options (void);
//        void line_limit (void);

    private:
	cmd_opts_t opts;
        char**ARGV;
        int ARGC;
        void string2cmdline(int &,char**&, string);
};

#endif
