/**
 * @file XlsFileTest.cpp
 *
 * csv2xls - convert csv files into one or more Excel(TM) files
 * Copyright (C) 2012  Marcel Schneider
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU GENERAL PUBLIC LICENSE
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU GENERAL PUBLIC LICENSE for more details.
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 *
 * Free Software Foundation Inc.
 * 51 Franklin Street
 * Fifth Floor
 * Boston
 * MA  02110-1301  USA *
 */
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
    delete xls_file.wbook;
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
    read_CSV_into(&xls_file,INPUT_ROWS,INPUT_COLUMNS);
    
    CPPUNIT_ASSERT ( 1 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( INPUT_ROWS * INPUT_COLUMNS == test_workbook->called_label );
    CPPUNIT_ASSERT ( 1 == test_workbook->called_write_to_file );
    CPPUNIT_ASSERT ( 0 == xls_file.current_column );

    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef LINE_LIMIT_PER_SHEET
}

void
XlsFileTest::
make_2_sheets_out_of_8_inputlines_with_headline(void)
{
    #define INPUT_COLUMNS         3
    #define INPUT_ROWS            8
    #define HEADLINE              1
    #define LINE_LIMIT_PER_SHEET  5

    std::vector<string>tmp(INPUT_COLUMNS,"head");
    xls_file.headline = tmp;
    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;

    read_CSV_into(&xls_file,INPUT_ROWS,INPUT_COLUMNS);
    CPPUNIT_ASSERT (  1 == test_workbook->called_clear_sheet );
    CPPUNIT_ASSERT ( (INPUT_ROWS + HEADLINE)* INPUT_COLUMNS
                        == test_workbook->called_label );

    CPPUNIT_ASSERT (  1 == test_workbook->called_write_to_file );
    CPPUNIT_ASSERT (  0 == xls_file.current_column );
    CPPUNIT_ASSERT (  INPUT_ROWS + HEADLINE - LINE_LIMIT_PER_SHEET
                        == xls_file.current_row );
    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef HEADLINE
    #undef LINE_LIMIT_PER_SHEET
}

void
XlsFileTest::
make_2x4_lines_sheets_out_of_8_inputlines_without_headline(void)
{
    #define INPUT_COLUMNS        3
    #define INPUT_ROWS           8
    #define LINE_LIMIT_PER_SHEET 4

    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;
    read_CSV_into(&xls_file,INPUT_ROWS,INPUT_COLUMNS);
    csv2xls::xls_dump_worksheet(&xls_file);

    CPPUNIT_ASSERT ( 2 == test_workbook->called_write_to_file );

    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef LINE_LIMIT_PER_SHEET
}

void
XlsFileTest::
make_3x2_lines_sheets_out_of_4_inputlines_with_headline(void)
{
    #define INPUT_COLUMNS        3
    #define INPUT_ROWS           4
    #define HEADLINE             1
    #define LINE_LIMIT_PER_SHEET 2

    std::vector<string>tmp(INPUT_COLUMNS,"head");
    xls_file.headline = tmp;
    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;
    
    read_CSV_into(&xls_file,INPUT_ROWS,INPUT_COLUMNS);
    csv2xls::xls_dump_worksheet(&xls_file);

    CPPUNIT_ASSERT ( 3 == test_workbook->called_write_to_file );

    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef HEADLINE
    #undef LINE_LIMIT_PER_SHEET

}

void 
XlsFileTest::
read_CSV_into(csv2xls::xls_file_t *xlsfile,int row_count, int column_count)
{
    for(int row = 0; row < row_count; row++)
    {
        for(int col = 0; col < column_count; col++)
        {
            csv2xls::xls_append_cell(xlsfile, "lol");
        }
        csv2xls::xls_newline(xlsfile);
    }

}