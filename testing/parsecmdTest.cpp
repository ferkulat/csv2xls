#include "parsecmdTest.hpp"
#include <stdlib.h>
#include <string.h>
#include <wordexp.h>


#include <cppunit/config/SourcePrefix.h>
CPPUNIT_TEST_SUITE_REGISTRATION (parsecmdTest);




void
parsecmdTest::
print_argv(int count, char**argv)
{
    for(int i = 0; i < count; ++i)
    {
        cerr << argv[i] << " ";
    }
    cerr << endl;
}


void parsecmdTest::setUp()
{
}

void parsecmdTest::tearDown(){}

void parsecmdTest::no_options()
{
    wordexp_t args;
    wordexp("csv2xls input1.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input1.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input1.csv"));
    wordfree(&args);

    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    wordexp("csv2xls tmp/input2.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("tmp/input2.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input2.csv"));
    wordfree(&args);

    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    wordexp("csv2xls /tmp/input3.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("/tmp/input3.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input3.csv"));
    wordfree(&args);
}

void parsecmdTest::output_dir()
{
    wordexp_t args;
    wordexp("csv2xls  -o/tmp/ input.csv", &args,0);
    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    parse_commandline(opts,args.we_wordc,args.we_wordv);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("/tmp/input.csv"));
    wordfree(&args);

    wordexp("csv2xls  -o tmp/ input1.csv", &args,0);
    opts.csv_file_name.clear();
    opts.xls_file_name.clear();
    parse_commandline(opts,args.we_wordc,args.we_wordv);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input1.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("tmp/input1.csv"));
    wordfree(&args);
}

void parsecmdTest::line_limit_0()
{
    wordexp_t args;
    wordexp("csv2xls -l0 input.csv", &args,0);
    CPPUNIT_ASSERT (0 == parse_commandline(opts,args.we_wordc,args.we_wordv));
    wordfree(&args);
}

void
parsecmdTest::line_limit_1()
{
    wordexp_t args;
    wordexp("csv2xls -l1 input.csv", &args,0);
    CPPUNIT_ASSERT (0 == parse_commandline(opts,args.we_wordc,args.we_wordv));
    wordfree(&args);
}

void
parsecmdTest::line_limit_2()
{
    wordexp_t args;
    wordexp("csv2xls -l2 input.csv", &args,0);
    CPPUNIT_ASSERT (1 == parse_commandline(opts,args.we_wordc,args.we_wordv));
    wordfree(&args);
}


