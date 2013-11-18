#include "../src/parsecmd.hpp"
#include <wordexp.h>
#include "CppUTest/TestHarness.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


using namespace std;

using namespace csv2xls;


TEST_GROUP(Group1)
{
    cmd_opts_t opts;
    wordexp_t  args;

   void setup()
   {
    optind = 1;
    opts.csv_file_name.clear();
    opts.xls_file_name.clear();


      // Init stuff
   }

   void teardown()
   {
        wordfree(&args);
      // Uninit stuff
   }	
};

TEST(Group1,no_options)
{
    wordexp("csv2xls input1.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CHECK        ( ! opts.csv_file_has_headline             );
    LONGS_EQUAL  ( 65536,        opts.xls_row_limit         );
    STRCMP_EQUAL ( "input1.csv", opts.csv_file_name.c_str() );
    STRCMP_EQUAL ( "input1.csv", opts.xls_file_name.c_str() );
}

TEST(Group1,no_options_subdir)
{
    wordexp("csv2xls tmp/input2.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CHECK        ( ! opts.csv_file_has_headline                 );
    LONGS_EQUAL  ( 65536,            opts.xls_row_limit         );
    STRCMP_EQUAL ( "tmp/input2.csv", opts.csv_file_name.c_str() );
    STRCMP_EQUAL ( "input2.csv",     opts.xls_file_name.c_str() );
}

TEST(Group1,no_options_absolute_path)
{

    wordexp("csv2xls /tmp/input3.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    CHECK        ( ! opts.csv_file_has_headline                  );
    LONGS_EQUAL  ( 65536,             opts.xls_row_limit         );
    STRCMP_EQUAL ( "/tmp/input3.csv", opts.csv_file_name.c_str() );
    STRCMP_EQUAL ( "input3.csv",      opts.xls_file_name.c_str() );
}

 TEST(Group1,output_dir_absolute)
{
    wordexp("csv2xls  -o/tmp/ input.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    STRCMP_EQUAL ( "input.csv",      opts.csv_file_name.c_str() );
    STRCMP_EQUAL ( "/tmp/input.csv", opts.xls_file_name.c_str() );
}

 TEST(Group1,output_dir_relative)
{
    wordexp("csv2xls  -o tmp/ input1.csv", &args,0);
    parse_commandline(opts,args.we_wordc,args.we_wordv);

    STRCMP_EQUAL ( "input1.csv",     opts.csv_file_name.c_str() );
    STRCMP_EQUAL ( "tmp/input1.csv", opts.xls_file_name.c_str() );
}

 TEST(Group1,line_limit_0)
{
    wordexp("csv2xls -l0 input.csv", &args,0);
    CHECK ( ! parse_commandline(opts,args.we_wordc,args.we_wordv));
}


TEST(Group1,line_limit_1)
{
    wordexp("csv2xls -l1 input.csv", &args,0);
    CHECK ( ! parse_commandline(opts,args.we_wordc,args.we_wordv));
}


TEST(Group1,line_limit_2)
{
    wordexp("csv2xls -l2 input.csv", &args,0);
    CHECK (1 == parse_commandline(opts,args.we_wordc,args.we_wordv));
}

