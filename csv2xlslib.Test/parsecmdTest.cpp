#include <vector>
#include <algorithm>
#include <iostream>
#include <getopt.h>
#include "../csv2xlslib/parsecmd.hpp"
#include "doctest.h"

using namespace std;

using namespace csv2xls;

struct TheFixture
{
    opts_t opts;
    TheFixture() = default;

    virtual ~TheFixture() = default;
};




TEST_CASE_FIXTURE(TheFixture, "When_no_commandline_options_are_given then set_default_values")
{
    opts.csv_file_name = "input1.csv";

    opts_t actual;
    REQUIRE_NOTHROW(actual = checkOptions(opts));
    CHECK(!actual.csv_file_has_headline);
    CHECK_EQ(DEFAULT_CSV_TAB_DELIMITER, actual.csv_tab_delimiter);
    CHECK_EQ(DEFAULT_XLS_MAX_LINES,     actual.xls_row_limit);
    CHECK_EQ(DEFAULT_XLS_DIGIT_COUNT,   actual.xls_digit_count);
    CHECK_EQ(DEFAULT_CSV_BUFFER_SIZE,   actual.input_buffer_size);
    CHECK_EQ(DEFAULT_XLS_SHEET_NAME,    actual.xls_sheet_name);

}

TEST_CASE_FIXTURE(TheFixture, "When_no_commandline_options_are_given then guess_output_name_from_inputname")
{
    opts.csv_file_name = "input1.csv";
    opts_t actual;
    REQUIRE_NOTHROW(actual = set_xls_filename(opts));
    CHECK_EQ("input1.csv", actual.csv_file_name);
    CHECK_EQ("input1.xls", actual.xls_file_name);
}

TEST_CASE_FIXTURE(TheFixture, "When_output_name_is_a_directory, guess_output_name_from_inputname")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_file_name = "tmp/";

    opts_t actual;
    REQUIRE_NOTHROW(actual = set_xls_filename(opts));
    CHECK_EQ("input1.csv",     actual.csv_file_name);
    CHECK_EQ("tmp/input1.xls", actual.xls_file_name);
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_headline then it_should_fail_with_line_limit_1")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 1;
    opts.csv_file_has_headline = true;

    REQUIRE_THROWS(checkOptions(opts));
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_headline then it_accepts_line_limit_set_to_2")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 2;
    opts.csv_file_has_headline = true;

    REQUIRE_NOTHROW(checkOptions(opts));
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_not_headline then it_accepts_line_limit_set_to_1")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 1;
    opts.csv_file_has_headline = false;

    REQUIRE_NOTHROW(checkOptions(opts));
}

TEST_CASE_FIXTURE(TheFixture, "When_line_limit_is_0 then it_should_fail")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 0;

    REQUIRE_THROWS(checkOptions(opts));
}
auto CmdArgsArray(std::vector<std::string>&args){
    optind = 1;
    std::vector<char *> arg_ptrs(args.size(), nullptr);
    auto const IntoPtr = [](std::string & str){ return str.data();};
    std::transform(std::begin(args), std::end(args),std::begin(arg_ptrs), IntoPtr);
    return arg_ptrs;
}

TEST_CASE("Option v should not throw")
{
    std::vector<std::string> args{"prgname", "-v"};
    auto arg_ptrs = CmdArgsArray(args);

    REQUIRE_NOTHROW(parsecmd_getopts(static_cast<int>(arg_ptrs.size()), arg_ptrs.data()));

}

TEST_CASE("Option h should not throw")
{
    std::vector<std::string> args{"prgname", "-h"};
    auto arg_ptrs = CmdArgsArray(args);

    REQUIRE_NOTHROW(parsecmd_getopts(static_cast<int>(arg_ptrs.size()), arg_ptrs.data()));

}