#include "XlsFileTest.hpp"
#include <vector>
#include <cppunit/config/SourcePrefix.h>
CPPUNIT_TEST_SUITE_REGISTRATION (XlsFileTest);

void
XlsFileTest::
setUp()
{
    test_workbook           = new dummy_workbook();
    xls_file.wbook          = test_workbook;
    xls_file.filename       = "file";
    xls_file.xls_row_limit  = XLS_MAX_ROWS;
    xls_file.current_column = 0;
    xls_file.current_row    = 0;
}

void
XlsFileTest::
tearDown()
{
    xls_file.wbook->~workbook();
}

void
XlsFileTest::
xls_append_cell_increases_column (void)
{
    xls_file.current_column = 0;
    xls_file.current_row = 0;
    csv2xls::xls_append_cell(&xls_file,"lol");
    CPPUNIT_ASSERT ( 0 == xls_file.current_row );
    CPPUNIT_ASSERT ( 1 == xls_file.current_column );
}

void
XlsFileTest::
xls_append_cell_ignores_columns_greater_than_XLS_MAX_COLUMNS (void)
{
    xls_file.current_column = XLS_MAX_COLUMNS ;
    xls_file.current_row = 0;
    csv2xls::xls_append_cell(&xls_file,"lol");
    CPPUNIT_ASSERT ( 0 == xls_file.current_row );
    CPPUNIT_ASSERT ( XLS_MAX_COLUMNS == xls_file.current_column );
}
void
XlsFileTest::
xls_newline_increases_row (void)
{
    xls_file.current_column = 0;
    xls_file.current_row = 0;
    csv2xls::xls_newline(&xls_file);
    CPPUNIT_ASSERT ( 0 == xls_file.current_column );
    CPPUNIT_ASSERT ( 1 == xls_file.current_row );
    CPPUNIT_ASSERT ( 0 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( 0 == test_workbook->called_write_to_file );

}

void
XlsFileTest::
xls_newline_writes_sheet_into_file_and_makes_a_new_sheet_if_row_is_XLS_MAX_ROWS (void)
{
    xls_file.current_column = 2;
    xls_file.current_row = XLS_MAX_ROWS;
    csv2xls::xls_newline(&xls_file);
    CPPUNIT_ASSERT ( 1 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( 1 == test_workbook->called_write_to_file );
    CPPUNIT_ASSERT ( 0 == xls_file.current_column );
    CPPUNIT_ASSERT ( 0 == xls_file.current_row );

}

void
XlsFileTest::
xls_add_headline_does_nothing_if_headline_is_empty(void)
{
    xls_file.headline.clear();
    csv2xls::xls_add_headline(&xls_file);
    CPPUNIT_ASSERT ( 0 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( 0 == test_workbook->called_label );
    CPPUNIT_ASSERT ( 0 == test_workbook->called_write_to_file );
    CPPUNIT_ASSERT ( 0 == xls_file.current_column );
    CPPUNIT_ASSERT ( 0 == xls_file.current_row );
}

void
XlsFileTest::
xls_add_headline_includes_a_newline(void)
{
    std::vector<string>tmp(4,"lol");
    xls_file.headline = tmp;
    csv2xls::xls_add_headline(&xls_file);
    CPPUNIT_ASSERT ( 0 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( 4 == test_workbook->called_label );
    CPPUNIT_ASSERT ( 0 == test_workbook->called_write_to_file );
    CPPUNIT_ASSERT ( 0 == xls_file.current_column );
    CPPUNIT_ASSERT ( 1 == xls_file.current_row );
}

void
XlsFileTest::
make_2_sheets_out_of_8_inputlines_without_headline(void)
{
    #define INPUT_COLUMNS        3
    #define INPUT_ROWS           8
    #define LINE_LIMIT_PER_SHEET 5

    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;
    for(int row = 0; row < INPUT_ROWS; row++)
    {
        for(int col = 0; col < INPUT_COLUMNS; col++)
        {
            csv2xls::xls_append_cell(&xls_file, "lol");
        }
        csv2xls::xls_newline(&xls_file);
    }
    CPPUNIT_ASSERT ( 1 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( INPUT_ROWS * INPUT_COLUMNS == test_workbook->called_label );
    CPPUNIT_ASSERT ( 1 == test_workbook->called_write_to_file );
    CPPUNIT_ASSERT ( 0 == xls_file.current_column );
    CPPUNIT_ASSERT ( INPUT_ROWS - LINE_LIMIT_PER_SHEET == xls_file.current_row );
}

void
XlsFileTest::
make_2_sheets_out_of_8_inputlines_with_headline(void)
{
    #define INPUT_COLUMNS 3
    #define INPUT_ROWS    8
    #define HEADLINE      1
    #define LINE_LIMIT_PER_SHEET 5

    std::vector<string>tmp(INPUT_COLUMNS,"head");
    xls_file.headline = tmp;
    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;

    std::vector<string>::iterator first = xls_file.headline.begin();
    std::vector<string>::iterator last  = xls_file.headline.end();
    for(; first != last; first++)
    {
        csv2xls::xls_append_cell(&xls_file, *first);
    }
    csv2xls::xls_newline(&xls_file);

    for(int row = 0; row< (INPUT_ROWS - HEADLINE) ; row++)
    {
        for(int col = 0; col < INPUT_COLUMNS; col++)
        {
            csv2xls::xls_append_cell(&xls_file, "lol");
        }
        csv2xls::xls_newline(&xls_file);
    }
    CPPUNIT_ASSERT (  1 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( (INPUT_ROWS + HEADLINE)* INPUT_COLUMNS
                        == test_workbook->called_label );
    
    CPPUNIT_ASSERT (  1 == test_workbook->called_write_to_file );
    CPPUNIT_ASSERT (  0 == xls_file.current_column );
    CPPUNIT_ASSERT (  INPUT_ROWS + HEADLINE - LINE_LIMIT_PER_SHEET
                        == xls_file.current_row );
}