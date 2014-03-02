#include "../src/parsecmd.hpp"
#include "CppUTest/TestHarness.h"

using namespace std;

using namespace csv2xls;

TEST_GROUP(When_no_commandline_options_are_given)
{
	opts_t opts;

	void setup()
	{
		csv_set_default_values(opts);
		xls_set_default_values(opts);
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}
};

TEST_GROUP(When_output_name_is_a_directory)
{
	opts_t opts;

	void setup()
	{
		csv_set_default_values(opts);
		xls_set_default_values(opts);
	}

	void teardown()
	{
		// Uninit stuff
	}
};

TEST_GROUP(When_first_line_is_headline)
{
	opts_t opts;

	void setup()
	{
		csv_set_default_values(opts);
		xls_set_default_values(opts);
	}

	void teardown()
	{
		// Uninit stuff
	}
};

TEST_GROUP(When_first_line_is_not_headline)
{
	opts_t opts;

	void setup()
	{
		csv_set_default_values(opts);
		xls_set_default_values(opts);
	}

	void teardown()
	{
		// Uninit stuff
	}
};

TEST_GROUP(When_line_limit_is_0)
{
	opts_t opts;

	void setup()
	{
		csv_set_default_values(opts);
		xls_set_default_values(opts);
	}

	void teardown()
	{
		// Uninit stuff
	}
};

TEST(When_no_commandline_options_are_given, set_default_values)
{
	opts.csv_file_name = "input1.csv";

	CHECK(checkOptions(opts));
	CHECK(!opts.csv_file_has_headline);
	LONGS_EQUAL(DEFAULT_CSV_TAB_DELIMITER, opts.csv_tab_delimiter);
	LONGS_EQUAL(DEFAULT_XLS_MAX_LINES, opts.xls_row_limit);
	LONGS_EQUAL(DEFAULT_XLS_DIGIT_COUNT, opts.xls_digit_count);
	LONGS_EQUAL(DEFAULT_CSV_BUFFER_SIZE, opts.input_buffer_size);
	STRCMP_EQUAL(DEFAULT_XLS_SHEET_NAME, opts.xls_sheet_name.c_str());

}

TEST(When_no_commandline_options_are_given, guess_output_name_from_inputname)
{
	opts.csv_file_name = "input1.csv";

	CHECK(checkOptions(opts));
	STRCMP_EQUAL("input1.csv", opts.csv_file_name.c_str());
	STRCMP_EQUAL("input1.xls", opts.xls_file_name.c_str());
}

TEST(When_output_name_is_a_directory, guess_output_name_from_inputname)
{
	opts.csv_file_name = "input1.csv";
	opts.xls_file_name = "tmp/";

	CHECK(checkOptions(opts));
	STRCMP_EQUAL("input1.csv", opts.csv_file_name.c_str());
	STRCMP_EQUAL("tmp/input1.xls", opts.xls_file_name.c_str());
}

TEST(When_first_line_is_headline, it_should_fail_with_line_limit_1)
{
	opts.csv_file_name = "input1.csv";
	opts.xls_row_limit = 1;
	opts.csv_file_has_headline = true;

	CHECK(!checkOptions(opts));
}

TEST(When_first_line_is_headline, it_accepts_line_limit_set_to_2)
{
	opts.csv_file_name = "input1.csv";
	opts.xls_row_limit = 2;
	opts.csv_file_has_headline = true;

	CHECK(checkOptions(opts));
}

TEST(When_first_line_is_not_headline, it_accepts_line_limit_set_to_1)
{
	opts.csv_file_name = "input1.csv";
	opts.xls_row_limit = 1;
	opts.csv_file_has_headline = false;

	CHECK(checkOptions(opts));
}

TEST(When_line_limit_is_0, it_should_fail)
{
	opts.csv_file_name = "input1.csv";
	opts.xls_row_limit = 0;

	CHECK(!checkOptions(opts));
}
