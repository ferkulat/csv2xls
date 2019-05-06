#include <XlsFile.hpp>
#include <default_values.h>
#include <catch.hpp>
namespace csv2xls
{
using namespace std;
class dummy_workbook
{
  public:
    dummy_workbook()
    {
        called_clear_sheet   = 0;
        called_write_to_file = 0;
        called_label         = 0;
    }

    void clearSheet(XlsSheetName const& /*sheetname*/)
    {
        called_clear_sheet++;
    }
    int writeInto(OutputFileName const& /*file_name*/)
    {
        called_write_to_file++;
        return 0;
    }
    void setCell(Row /*row*/, Column /*col*/, CellContent const& /*strlabel*/)
    {
        called_label++;
    }
    int called_clear_sheet;
    int called_write_to_file;
    int called_label;
};
template <typename T> class wrapper_workbook
{
    std::shared_ptr<T> wrapped;

  public:
    wrapper_workbook(std::shared_ptr<T> wrapped_)
        : wrapped(wrapped_)
    {
    }

    void clearSheet(XlsSheetName const& sheet_name)
    {
        wrapped->clearSheet(sheet_name);
    }
    int writeInto(OutputFileName const& file_name)
    {
        return wrapped->writeInto(file_name);
    }
    void setCell(Row row, Column column, CellContent const& cell_content)
    {
        wrapped->setCell(row, column, cell_content);
    }
};

void read_CSV_into(csv2xls::xls_file_t& xlsfile, int row_count, int column_count)
{
    for (int row = 0; row < row_count; row++)
    {
        for (int col = 0; col < column_count; col++)
        {
            csv2xls::appendCell(xlsfile, CellContent("lol"));
        }
        csv2xls::newLine(xlsfile);
    }
}

struct Group1
{
    std::shared_ptr<dummy_workbook>      test_workbook;
    csv2xls::xls_file_t xls_file{OutputDoc(wrapper_workbook(test_workbook))};

    Group1()
    {
        test_workbook             = std::make_shared<dummy_workbook>();
        xls_file                  = csv2xls::xls_file_t(OutputDoc(wrapper_workbook(test_workbook)));
        xls_file.output_file_name = OutputFileName("file");
        xls_file.xls_row_limit    = csv2xls::DEFAULT_XLS_MAX_LINES;
        xls_file.current_column   = Column(0);
        xls_file.current_row      = Row(0);
        xls_file.digit_count      = DigitCount(3);
        xls_file.file_number      = FileNumber(0);
    }

    virtual ~Group1() = default;
};
TEST_CASE_METHOD(Group1, "xls_append_cell_increases_column")
{
    xls_file.current_column = Column(0);
    xls_file.current_row    = Row(0);

    csv2xls::appendCell(xls_file, CellContent("lol"));
    REQUIRE(Row(0)    == xls_file.current_row);
    REQUIRE(Column(1) == xls_file.current_column);
}

TEST_CASE_METHOD(Group1, "xls_append_cell_ignores_columns_greater_than_XLS_MAX_COLUMNS")
{
    xls_file.current_column = Column(csv2xls::XLS_MAX_COLUMNS.Get());
    xls_file.current_row    = Row(0);
    
    csv2xls::appendCell(xls_file, CellContent("lol"));

    REQUIRE(Row(0) == xls_file.current_row);
    REQUIRE(xls_file.current_column.isEqual(csv2xls::XLS_MAX_COLUMNS));
}

TEST_CASE_METHOD(Group1, "xls_newline_increases_row")
{
    xls_file.current_column = Column(0);
    xls_file.current_row    = Row(0);

    csv2xls::newLine(xls_file);

    REQUIRE(Column(0) == xls_file.current_column);
    REQUIRE(Row(1)    == xls_file.current_row);
    REQUIRE(0         == test_workbook->called_clear_sheet);
    REQUIRE(0         == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Group1, "xls_add_headline_does_nothing_if_headline_is_empty")
{
    xls_file.headline.clear();
    csv2xls::addHeadline(xls_file);

    CHECK(0         == test_workbook->called_clear_sheet);
    CHECK(0         == test_workbook->called_label);
    CHECK(0         == test_workbook->called_write_to_file);
    CHECK(Column(0) == xls_file.current_column);
    CHECK(Row(0)    == xls_file.current_row);
}

TEST_CASE_METHOD(Group1, "xls_add_headline_includes_a_newline")
{

    xls_file.headline = std::vector<CellContent>(4, CellContent("lol"));

    csv2xls::addHeadline(xls_file);

    CHECK(0         == test_workbook->called_clear_sheet);
    CHECK(4         == test_workbook->called_label);
    CHECK(0         == test_workbook->called_write_to_file);
    CHECK(Column(0) == xls_file.current_column);
    CHECK(Row(1)    == xls_file.current_row);
}

TEST_CASE_METHOD(Group1, "xls_newline_writes_sheet_into_file_and_makes_a_new_sheet_if_row_is_XLS_MAX_ROWS")
{
    xls_file.current_column = Column(2);
    xls_file.current_row    = Row(csv2xls::XLS_MAX_ROWS.Get());
    csv2xls::newLine(xls_file);
    
    CHECK(1         == test_workbook->called_clear_sheet);
    CHECK(1         == test_workbook->called_write_to_file);
    CHECK(Column(0) == xls_file.current_column);
    CHECK(Row(0)    == xls_file.current_row);
}

TEST_CASE_METHOD(Group1, "make_2_sheets_out_of_8_inputlines_without_headline")
{
    constexpr size_t INPUT_COLUMNS        = 3;
    constexpr size_t INPUT_ROWS           = 8;
    constexpr auto   LINE_LIMIT_PER_SHEET = OutputRowLimit(5);

    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;
    read_CSV_into(xls_file, INPUT_ROWS, INPUT_COLUMNS);

    CHECK(1 == test_workbook->called_clear_sheet);
    CHECK(INPUT_ROWS * INPUT_COLUMNS == test_workbook->called_label);
    CHECK(1 == test_workbook->called_write_to_file);
    CHECK(Column(0) == xls_file.current_column);
}

TEST_CASE_METHOD(Group1, "make_2_sheets_out_of_8_inputlines_with_headline")
{
    constexpr size_t INPUT_COLUMNS        = 3;
    constexpr size_t INPUT_ROWS           = 8;
    constexpr size_t HEADLINE             = 1;
    constexpr auto   LINE_LIMIT_PER_SHEET = OutputRowLimit(5);

    xls_file.headline      = std::vector<CellContent>(INPUT_COLUMNS, CellContent("head"));
    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;

    read_CSV_into(xls_file, INPUT_ROWS, INPUT_COLUMNS);
    CHECK(1 == test_workbook->called_clear_sheet);
    CHECK((INPUT_ROWS + HEADLINE) * INPUT_COLUMNS == test_workbook->called_label);

    CHECK(1 == test_workbook->called_write_to_file);
    CHECK(Column(0) == xls_file.current_column);
    CHECK(INPUT_ROWS + HEADLINE - LINE_LIMIT_PER_SHEET.Get() == xls_file.current_row.Get());
}

TEST_CASE_METHOD(Group1, "make_2x4_lines_sheets_out_of_8_inputlines_without_headline")
{
    constexpr size_t INPUT_COLUMNS        = 3;
    constexpr size_t INPUT_ROWS           = 8;
    constexpr auto   LINE_LIMIT_PER_SHEET = OutputRowLimit(4);

    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;
    read_CSV_into(xls_file, INPUT_ROWS, INPUT_COLUMNS);
    csv2xls::writeIntoFile(xls_file);

    CHECK(2 == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Group1, "make_3x2_lines_sheets_out_of_4_inputlines_with_headline")
{
    constexpr size_t INPUT_COLUMNS        = 3;
    constexpr size_t INPUT_ROWS           = 4;
    constexpr auto   LINE_LIMIT_PER_SHEET = OutputRowLimit(2);

    xls_file.headline      = std::vector<CellContent>(INPUT_COLUMNS, CellContent("head"));
    xls_file.xls_row_limit = LINE_LIMIT_PER_SHEET;

    read_CSV_into(xls_file, INPUT_ROWS, INPUT_COLUMNS);
    csv2xls::writeIntoFile(xls_file);

    CHECK(3 == test_workbook->called_write_to_file);
}
}
