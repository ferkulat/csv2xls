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
    CPPUNIT_TEST (line_limit_0);
    CPPUNIT_TEST (line_limit_1);
    CPPUNIT_TEST (line_limit_2);
    CPPUNIT_TEST (output_dir);

    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void no_options (void);
        void line_limit_0 (void);
        void line_limit_1 (void);
        void line_limit_2 (void);
        void output_dir(void);
    private:
	cmd_opts_t opts;
        void print_argv(int ,char**);
};

#endif
