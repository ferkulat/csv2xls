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
void parsecmdTest::setUp(){}
void parsecmdTest::tearDown(){}

void parsecmdTest::no_options()
{
    string line;
    line.assign("csv2xls input.csv");
    string2cmdline(ARGC,ARGV,line);
    parse_commandline(opts,ARGC,ARGV);

    CPPUNIT_ASSERT (false == opts.csv_file_has_headline);
    CPPUNIT_ASSERT (65536 == (int)opts.xls_row_limit);
    CPPUNIT_ASSERT (0 == opts.csv_file_name.compare("input.csv"));
    CPPUNIT_ASSERT (0 == opts.xls_file_name.compare("input.csv"));
}

//void parsecmdTest::line_limit(){
//	CPPUNIT_ASSERT_EQUAL (0,filename("input.xls",0).compare("input.xls"));
//	CPPUNIT_ASSERT_EQUAL (0,filename("input.Xls",0).compare("input.Xls"));
//	CPPUNIT_ASSERT_EQUAL (0,filename("input.XLS",1).compare("input0001.XLS"));
//}


