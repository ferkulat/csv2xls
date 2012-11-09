#include "parsecmdTest.hpp"
#include <stdlib.h>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <vector>

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

#include <cppunit/config/SourcePrefix.h>
CPPUNIT_TEST_SUITE_REGISTRATION (parsecmdTest);
void
parsecmdTest::
string2cmdline(int &count ,char**&argv,string line)
{

    tokenizer::iterator tok_iter;
    char delim[] = {' ','\0'};
    boost::char_separator<char> sep(delim, "");
    tokenizer tokens(line, sep);
    vector<string> tokenlist ;
    for (tok_iter = tokens.begin();tok_iter != tokens.end(); ++tok_iter)
    {
        tokenlist.push_back( *tok_iter) ;
    }
    count = tokenlist.size();
    argv  = (char**) malloc(sizeof(char**)*count);

    for (int i = 0;i < count;i++)
    {
        argv[i] = (char*) malloc(tokenlist[i].size()+1);
        tokenlist[i].copy(argv[i],tokenlist[i].size(),0);
        argv[i][tokenlist[i].size()] = '\0';
    }
}

void
parsecmdTest::
print_argv(int count ,char**argv)
{
    for(int i=0;i<count;++i)
    {
        cerr << argv[i]<< " ";
    }
    cerr << endl;
}

void
parsecmdTest::
clean_command_line(int &count ,char**&argv)
{
    for (int i=count-1;i>=0;--i)
    {
        free(argv[i]);
    }
    free(argv);
}

void parsecmdTest::setUp()
{
}

void parsecmdTest::tearDown(){}

void parsecmdTest::no_options()
{
    char**ARGV;
    int ARGC;
    line.assign("csv2xls input.csv");
    string2cmdline(ARGC,ARGV,line);
    parse_commandline(opts,ARGC,ARGV);
    clean_command_line(ARGC,ARGV);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input.csv"));
}

void parsecmdTest::line_limit_0()
{
    char**ARGV_0;
    int ARGC_0;
    line.assign("csv2xls -l0 input.csv");
    string2cmdline(ARGC_0,ARGV_0,line);
    CPPUNIT_ASSERT (0 == parse_commandline(opts,ARGC_0,ARGV_0));
    clean_command_line(ARGC_0,ARGV_0);
}

void 
parsecmdTest::line_limit_1()
{
    char**ARGV_1;
    int ARGC_1;
    line.assign("csv2xls -l1 input.csv");
    string2cmdline(ARGC_1,ARGV_1,line);
    CPPUNIT_ASSERT (0 == parse_commandline(opts,ARGC_1,ARGV_1));
    clean_command_line(ARGC_1,ARGV_1);
}

void 
parsecmdTest::line_limit_2()
{
    char**ARGV_2;
    int ARGC_2;
    line.assign("csv2xls -l2 input.csv");
    string2cmdline(ARGC_2,ARGV_2,line);
    CPPUNIT_ASSERT (1 == parse_commandline(opts,ARGC_2,ARGV_2));
    clean_command_line(ARGC_2,ARGV_2);
}


