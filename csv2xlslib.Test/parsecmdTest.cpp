#include <vector>
#include <algorithm>
#include <iostream>
#include <getopt.h>
#include "../csv2xlslib/parsecmd.hpp"
#include "doctest.h"

using namespace std;

using namespace csv2xls;
auto CmdArgsArray(std::vector<std::string>&args){
    optind = 1;
    std::vector<char *> arg_ptrs(args.size(), nullptr);
    auto const IntoPtr = [](std::string & str){ return str.data();};
    std::transform(std::begin(args), std::end(args),std::begin(arg_ptrs), IntoPtr);
    return arg_ptrs;
}

struct TheFixture
{
    Config opts;
    TheFixture() = default;
    XlsSheetName const DEFAULT_XLS_SHEET_NAME = XlsSheetName("Table1");

    virtual ~TheFixture() = default;
};

TEST_CASE_FIXTURE(TheFixture, "When_no_commandline_options_are_given then set_default_values")
{
    std::vector<std::string> args{"prgname", "input1.csv"};

    auto arg_ptrs      = CmdArgsArray(args);
    auto const my_opts = parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data());

    CHECK(!my_opts.csv_file_has_headline.Get());
    CHECK_EQ(DEFAULT_CSV_TAB_DELIMITER, my_opts.csv_tab_delimiter);
    CHECK_EQ(DEFAULT_XLS_MAX_LINES,     my_opts.xls_row_limit);
    CHECK_EQ(DEFAULT_XLS_DIGIT_COUNT,   my_opts.xls_digit_count);
    CHECK_EQ(DEFAULT_CSV_BUFFER_SIZE,   my_opts.input_buffer_size);
    CHECK_EQ(DEFAULT_XLS_SHEET_NAME,    my_opts.xls_sheet_name);
}

TEST_CASE_FIXTURE(TheFixture, "When_no_commandline_options_are_given then guess_output_name_from_inputname")
{
    std::vector<std::string> args{"prgname", "input1.csv"};

    auto arg_ptrs      = CmdArgsArray(args);
    auto const my_opts = parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data());

    CHECK_EQ(InputFile("input1.csv"), my_opts.csv_file_name);
    CHECK_EQ("input1.xls",            my_opts.xls_file_name);
}

TEST_CASE_FIXTURE(TheFixture, "When_output_name_is_a_directory, guess_output_name_from_inputname")
{
    std::vector<std::string> args{"prgname", "-o tmp/", "input1.csv"};

    auto arg_ptrs      = CmdArgsArray(args);
    auto const my_opts = parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data());

    CHECK_EQ(InputFile("input1.csv"), my_opts.csv_file_name);
    CHECK_EQ("tmp/input1.xls",        my_opts.xls_file_name);
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_headline then it_should_fail_with_line_limit_1")
{
    std::vector<std::string> args{"prgname", "-l 1", "-H", "input1.csv"};

    auto arg_ptrs = CmdArgsArray(args);
    REQUIRE_THROWS(parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data()));
}

TEST_CASE_FIXTURE(TheFixture, "When user requests -l 65536 it_should_not throw")
{
    std::vector<std::string> args{"prgname", "-l 65536", "-H", "input1.csv"};

    auto arg_ptrs = CmdArgsArray(args);
    auto my_opts  = parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data());

    REQUIRE_NOTHROW(checkOptions(opts));
}

TEST_CASE_FIXTURE(TheFixture, "When user requests -l 65537 it_should_ throw")
{
    std::vector<std::string> args{"prgname", "-l 65537", "-H", "input1.csv"};

    auto arg_ptrs = CmdArgsArray(args);

    REQUIRE_THROWS(parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data()));
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_headline then it_accepts_line_limit_set_to_2")
{
    std::vector<std::string> args{"prgname", "-l 2", "-H", "input1.csv"};

    auto arg_ptrs      = CmdArgsArray(args);
    auto const my_opts = parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data());

    CHECK_EQ(my_opts.csv_file_name,         InputFile("input1.csv"));
    CHECK_EQ(my_opts.xls_row_limit,         OutPutRowLimit(2));
    CHECK_EQ(my_opts.csv_file_has_headline, InputHasHeadLine(true));
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_not_headline then it_accepts_line_limit_set_to_1")
{
    std::vector<std::string> args{"prgname", "-l 1", "input1.csv"};
    
    auto arg_ptrs      = CmdArgsArray(args);
    auto const my_opts = parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data());

    CHECK_EQ(my_opts.xls_row_limit, OutPutRowLimit(1));
}

TEST_CASE_FIXTURE(TheFixture, "When_line_limit_is_0 then it_should_fail")
{
    std::vector<std::string> args{"prgname", "-l 0", "input1.csv"};

    auto arg_ptrs = CmdArgsArray(args);

    REQUIRE_THROWS(parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data()));
}

TEST_CASE("Option v should not throw")
{
    std::vector<std::string> args{"prgname", "-v"};

    auto arg_ptrs = CmdArgsArray(args);

    REQUIRE_NOTHROW(parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data()));

}

TEST_CASE("Option h should not throw")
{
    std::vector<std::string> args{"prgname", "-h"};
    auto arg_ptrs = CmdArgsArray(args);

    REQUIRE_NOTHROW(parse_commandline(static_cast<int>(arg_ptrs.size()), arg_ptrs.data()));

}