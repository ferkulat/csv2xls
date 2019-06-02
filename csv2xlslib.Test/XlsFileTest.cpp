#include "TestHelper.h"
#include <XlsFile.hpp>
#include <catch.hpp>
#include <default_values.h>
namespace csv2xls
{

void read_CSV_into(csv2xls::xls_file_t& xlsfile, Row row_count, Column column_count)
{
    for (auto row = Row(0); row < row_count; row++)
    {
        for (auto col = Column(0); col < column_count; col++)
        {
            auto lol = std::to_string(row.Get()) + "," + std::to_string(col.Get());
            csv2xls::appendCell(xlsfile, CellContent(lol.c_str(), lol.size()));
        }
        csv2xls::newLine(xlsfile);
    }
}

template<typename F>
void repeat(int count, F f)
{
    for (int i=0;i<count;++i)
        f();
}

struct Given_an_input_file_without_headline
{
    std::shared_ptr<Testing::DummyWorkBook>      test_workbook = std::make_shared<Testing::DummyWorkBook>();
    csv2xls::xls_file_t xls_file{OutputDoc(Testing::WrapperWorkBook(test_workbook))};

    Given_an_input_file_without_headline()
    {
        xls_file.xls_row_limit                = csv2xls::DEFAULT_XLS_MAX_LINES;
        xls_file.output_file_name.digit_count = DigitCount(3);
        xls_file.output_file_name.file_number = FileNumber(0);
    }

    virtual ~Given_an_input_file_without_headline() = default;
};

struct Given_an_input_file_with_headline
{
    std::shared_ptr<Testing::DummyWorkBook>      test_workbook = std::make_shared<Testing::DummyWorkBook>();
    csv2xls::xls_file_t xls_file{OutputDoc(Testing::WrapperWorkBook(test_workbook))};

    Given_an_input_file_with_headline()
    {
        xls_file.xls_row_limit                = csv2xls::DEFAULT_XLS_MAX_LINES;
        xls_file.output_file_name.digit_count = DigitCount(3);
        xls_file.output_file_name.file_number = FileNumber(0);
        xls_file.output_doc.setHeadLine({3,"lol"});
    }

    virtual ~Given_an_input_file_with_headline() = default;
};


TEST_CASE_METHOD(Given_an_input_file_without_headline, "xls_append_cell_increases_column")
{
    auto const * lol = "lol";

    auto const column = csv2xls::appendCell(xls_file, CellContent(lol,3));
    REQUIRE(Column(1) == column);
}

TEST_CASE_METHOD(Given_an_input_file_without_headline, "xls_append_cell_ignores_columns_greater_than_XLS_MAX_COLUMNS")
{
    auto const * lol = "lol";
    Column column(0);
    repeat(260, [&]{column = csv2xls::appendCell(xls_file, CellContent(lol, 3));});

    REQUIRE(column == Column(XLS_MAX_COLUMNS.Get()));
}

TEST_CASE_METHOD(Given_an_input_file_without_headline, "xls_newline_increases_row")
{

    auto const row = csv2xls::newLine(xls_file);

    REQUIRE(Row(1) == row);
    REQUIRE(0      == test_workbook->called_clear_sheet);
    REQUIRE(0      == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Given_an_input_file_without_headline, "xls_add_headline_does_nothing_if_headline_is_empty")
{

    CHECK(0 == test_workbook->called_clear_sheet);
    CHECK(0 == test_workbook->called_label);
    CHECK(0 == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Given_an_input_file_without_headline, "make_2_sheets_out_of_8_inputlines_without_headline")
{
    constexpr auto INPUT_COLUMNS        = Column(3);
    constexpr auto INPUT_ROWS           = Row(8);
    constexpr auto LINE_LIMIT_PER_SHEET = OutputRowLimit(5);

    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;
    read_CSV_into(xls_file, INPUT_ROWS, INPUT_COLUMNS);

    CHECK(1 == test_workbook->called_clear_sheet);
    CHECK(INPUT_ROWS.Get() * INPUT_COLUMNS.Get() == test_workbook->called_label);
    CHECK(1 == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Given_an_input_file_without_headline, "make_2x4_lines_sheets_out_of_8_inputlines_without_headline")
{
    constexpr auto INPUT_COLUMNS        = Column(3);
    constexpr auto INPUT_ROWS           = Row(8);
    constexpr auto LINE_LIMIT_PER_SHEET = OutputRowLimit(4);

    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;
    read_CSV_into(xls_file, INPUT_ROWS, INPUT_COLUMNS);
    csv2xls::writeIntoFile(xls_file);

    CHECK(2 == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Given_an_input_file_with_headline, "make_3x2_lines_sheets_out_of_4_inputlines_with_headline")
{
    constexpr auto INPUT_COLUMNS        = Column(3);
    constexpr auto INPUT_ROWS           = Row(4);
    constexpr auto LINE_LIMIT_PER_SHEET = OutputRowLimit(2);

    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;

    read_CSV_into(xls_file, INPUT_ROWS, INPUT_COLUMNS);
    csv2xls::writeIntoFile(xls_file);

    CHECK(3 == test_workbook->called_clear_sheet);
}
}
