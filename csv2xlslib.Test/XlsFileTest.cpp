#include <XlsFile.hpp>
#include "doctest.h"

using namespace std;
class dummy_workbook final : public csv2xls::workbook
{
public:
    dummy_workbook()
    {
        called_clear_sheet = 0;
        called_write_to_file = 0;
        called_label = 0;
    }

    void clear_sheet(const std::string& /*sheetname*/) override
    {
        called_clear_sheet++;
    }
    int write_to_file(const std::string&/*file_name*/) override
    {
        called_write_to_file++;
        return 0;
    }
    void label( unsigned int /*row*/,
                unsigned int /*col*/,
                const std::string& /*strlabel*/) override
    {
        called_label++;
    }
    int called_clear_sheet;
    int called_write_to_file;
    int called_label;

};

void read_CSV_into(csv2xls::xls_file_t *xlsfile,
                   int row_count,
                   int column_count)
{
    for (int row = 0; row < row_count; row++)
    {
        for (int col = 0; col < column_count; col++)
        {
            csv2xls::xls_append_cell(xlsfile, "lol");
        }
        csv2xls::xls_newline(xlsfile);
    }

}


struct Group1
{
    csv2xls::xls_file_t xls_file;
    dummy_workbook *test_workbook;

    Group1()
    {
        test_workbook = new dummy_workbook();
        xls_file.wbook.reset(test_workbook);
        xls_file.filename = "file";
        xls_file.xls_row_limit = csv2xls::XLS_MAX_ROWS;
        xls_file.current_column = 0;
        xls_file.current_row = 0;
        xls_file.digit_count = 3;
        xls_file.page_number = 0;
    }

    virtual ~Group1() = default;
};
TEST_CASE_FIXTURE(Group1,"xls_append_cell_increases_column")
{
    xls_file.current_column = 0;
    xls_file.current_row = 0;
    csv2xls::xls_append_cell(&xls_file, "lol");
    CHECK_EQ(0, xls_file.current_row);
    CHECK_EQ(1, xls_file.current_column);
}

TEST_CASE_FIXTURE(Group1, "xls_append_cell_ignores_columns_greater_than_XLS_MAX_COLUMNS" )
{
    xls_file.current_column = csv2xls::XLS_MAX_COLUMNS;
    xls_file.current_row = 0;
    csv2xls::xls_append_cell(&xls_file, "lol");
    CHECK_EQ(0, xls_file.current_row);
    CHECK_EQ(csv2xls::XLS_MAX_COLUMNS, xls_file.current_column);
}

TEST_CASE_FIXTURE(Group1, "xls_newline_increases_row" )
{
    xls_file.current_column = 0;
    xls_file.current_row = 0;
    csv2xls::xls_newline(&xls_file);
    CHECK_EQ(0, xls_file.current_column);
    CHECK_EQ(1, xls_file.current_row);
    CHECK_EQ(0, test_workbook->called_clear_sheet);
    CHECK_EQ(0, test_workbook->called_write_to_file);

}

TEST_CASE_FIXTURE(Group1, "xls_add_headline_does_nothing_if_headline_is_empty")
{
    xls_file.headline.clear();
    csv2xls::xls_add_headline(&xls_file);
    CHECK(0 == test_workbook->called_clear_sheet);
    CHECK(0 == test_workbook->called_label);
    CHECK(0 == test_workbook->called_write_to_file);
    CHECK(0 == xls_file.current_column);
    CHECK(0 == xls_file.current_row);
}

TEST_CASE_FIXTURE(Group1, "xls_add_headline_includes_a_newline")
{
    std::vector<string> tmp(4, "lol");
    xls_file.headline = tmp;
    csv2xls::xls_add_headline(&xls_file);
    CHECK(0 == test_workbook->called_clear_sheet);
    CHECK(4 == test_workbook->called_label);
    CHECK(0 == test_workbook->called_write_to_file);
    CHECK(0 == xls_file.current_column);
    CHECK(1 == xls_file.current_row);
}

TEST_CASE_FIXTURE(Group1, "xls_newline_writes_sheet_into_file_and_makes_a_new_sheet_if_row_is_XLS_MAX_ROWS" )
{
    xls_file.current_column = 2;
    xls_file.current_row = csv2xls::XLS_MAX_ROWS;
    csv2xls::xls_newline(&xls_file);
    CHECK(1 == test_workbook->called_clear_sheet);
    CHECK(1 == test_workbook->called_write_to_file);
    CHECK(0 == xls_file.current_column);
    CHECK(0 == xls_file.current_row);

}


TEST_CASE_FIXTURE(Group1, "make_2_sheets_out_of_8_inputlines_without_headline")
{
    constexpr size_t INPUT_COLUMNS        = 3;
    constexpr size_t INPUT_ROWS           = 8;
    constexpr size_t LINE_LIMIT_PER_SHEET = 5;

    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;
    read_CSV_into(&xls_file, INPUT_ROWS, INPUT_COLUMNS);

    CHECK(1 == test_workbook->called_clear_sheet);
    CHECK(INPUT_ROWS * INPUT_COLUMNS == test_workbook->called_label);
    CHECK(1 == test_workbook->called_write_to_file);
    CHECK(0 == xls_file.current_column);
}


TEST_CASE_FIXTURE(Group1, "make_2_sheets_out_of_8_inputlines_with_headline")
{
    constexpr size_t INPUT_COLUMNS         = 3;
    constexpr size_t INPUT_ROWS            = 8;
    constexpr size_t HEADLINE              = 1;
    constexpr size_t LINE_LIMIT_PER_SHEET  = 5;

    std::vector<string> tmp(INPUT_COLUMNS, "head");
    xls_file.headline = tmp;
    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;

    read_CSV_into(&xls_file, INPUT_ROWS, INPUT_COLUMNS);
    CHECK(1 == test_workbook->called_clear_sheet);
    CHECK((INPUT_ROWS + HEADLINE)* INPUT_COLUMNS == test_workbook->called_label);

    CHECK(1 == test_workbook->called_write_to_file);
    CHECK(0 == xls_file.current_column);
    CHECK(INPUT_ROWS + HEADLINE - LINE_LIMIT_PER_SHEET == xls_file.current_row);
}


TEST_CASE_FIXTURE(Group1, "make_2x4_lines_sheets_out_of_8_inputlines_without_headline")
{
    constexpr size_t INPUT_COLUMNS        = 3;
    constexpr size_t INPUT_ROWS           = 8;
    constexpr size_t LINE_LIMIT_PER_SHEET = 4;

    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;
    read_CSV_into(&xls_file, INPUT_ROWS, INPUT_COLUMNS);
    csv2xls::xls_dump_worksheet(&xls_file);

    CHECK(2 == test_workbook->called_write_to_file);
}



TEST_CASE_FIXTURE(Group1, "make_3x2_lines_sheets_out_of_4_inputlines_with_headline")
{
    constexpr size_t INPUT_COLUMNS        = 3;
    constexpr size_t INPUT_ROWS           = 4;
    constexpr size_t LINE_LIMIT_PER_SHEET = 2;

    std::vector<string> tmp(INPUT_COLUMNS, "head");
    xls_file.headline = tmp;
    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;

    read_CSV_into(&xls_file, INPUT_ROWS, INPUT_COLUMNS);
    csv2xls::xls_dump_worksheet(&xls_file);

    CHECK(3 == test_workbook->called_write_to_file);
}

