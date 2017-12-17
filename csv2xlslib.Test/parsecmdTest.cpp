#include "../csv2xlslib/parsecmd.hpp"
#include "doctest.h"

using namespace std;

using namespace csv2xls;

struct TheFixture
{
    opts_t opts;
    TheFixture()
    {
        csv_set_default_values(opts);
        xls_set_default_values(opts);
    }

    virtual ~TheFixture() {
        // teardown here
    }
};






TEST_CASE_FIXTURE(TheFixture, "When_no_commandline_options_are_given then set_default_values")
{
    opts.csv_file_name = "input1.csv";

    CHECK(checkOptions(opts));
    CHECK(!opts.csv_file_has_headline);
    CHECK_EQ(DEFAULT_CSV_TAB_DELIMITER, opts.csv_tab_delimiter);
    CHECK_EQ(DEFAULT_XLS_MAX_LINES, opts.xls_row_limit);
    CHECK_EQ(DEFAULT_XLS_DIGIT_COUNT, opts.xls_digit_count);
    CHECK_EQ(DEFAULT_CSV_BUFFER_SIZE, opts.input_buffer_size);
    CHECK_EQ(DEFAULT_XLS_SHEET_NAME, opts.xls_sheet_name);

}

TEST_CASE_FIXTURE(TheFixture, "When_no_commandline_options_are_given then guess_output_name_from_inputname")
{
    opts.csv_file_name = "input1.csv";

    CHECK(checkOptions(opts));
    CHECK_EQ("input1.csv", opts.csv_file_name);
    CHECK_EQ("input1.xls", opts.xls_file_name);
}

TEST_CASE_FIXTURE(TheFixture, "When_output_name_is_a_directory, guess_output_name_from_inputname")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_file_name = "tmp/";

    CHECK(checkOptions(opts));
    CHECK_EQ("input1.csv", opts.csv_file_name);
    CHECK_EQ("tmp/input1.xls", opts.xls_file_name);
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_headline then it_should_fail_with_line_limit_1")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 1;
    opts.csv_file_has_headline = true;

    CHECK(!checkOptions(opts));
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_headline then it_accepts_line_limit_set_to_2")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 2;
    opts.csv_file_has_headline = true;

    CHECK(checkOptions(opts));
}

TEST_CASE_FIXTURE(TheFixture, "When_first_line_is_not_headline then it_accepts_line_limit_set_to_1")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 1;
    opts.csv_file_has_headline = false;

    CHECK(checkOptions(opts));
}

TEST_CASE_FIXTURE(TheFixture, "When_line_limit_is_0 then it_should_fail")
{
    opts.csv_file_name = "input1.csv";
    opts.xls_row_limit = 0;

    CHECK(!checkOptions(opts));
}
