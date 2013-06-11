/**
 * @file XlsFileTest.hpp
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
#ifndef XLS_FILE_TEST_H
#define XLS_FILE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/XlsFile.hpp"
class dummy_workbook : public csv2xls::workbook
{
public:
             dummy_workbook(){called_clear_sheet   = 0;
                              called_write_to_file = 0;
                              called_label = 0;  };
    virtual ~dummy_workbook(){};

    virtual void clear_sheet(const std::string& sheetname){called_clear_sheet++;}
    virtual int  write_to_file(const std::string &file_name){called_write_to_file++;return 0;}
    virtual void label(unsigned int row,
                       unsigned int col,
                       const std::string& strlabel){called_label++;}
    int called_clear_sheet;
    int called_write_to_file;
    int called_label;

};

using namespace std;

class XlsFileTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (XlsFileTest);

    CPPUNIT_TEST (xls_append_cell_increases_column);
    CPPUNIT_TEST (xls_append_cell_ignores_columns_greater_than_XLS_MAX_COLUMNS);
    CPPUNIT_TEST (xls_newline_increases_row);
    CPPUNIT_TEST (xls_newline_writes_sheet_into_file_and_makes_a_new_sheet_if_row_is_XLS_MAX_ROWS);
    CPPUNIT_TEST (xls_add_headline_includes_a_newline);
    CPPUNIT_TEST (xls_add_headline_does_nothing_if_headline_is_empty);
    CPPUNIT_TEST (make_2_sheets_out_of_8_inputlines_without_headline);
    CPPUNIT_TEST (make_2_sheets_out_of_8_inputlines_with_headline);
    CPPUNIT_TEST (make_2x4_lines_sheets_out_of_8_inputlines_without_headline);
    CPPUNIT_TEST (make_3x2_lines_sheets_out_of_4_inputlines_with_headline);

//    CPPUNIT_TEST ();

    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void xls_append_cell_increases_column (void);
        void xls_append_cell_ignores_columns_greater_than_XLS_MAX_COLUMNS(void);
        void xls_newline_increases_row (void);
        void xls_newline_writes_sheet_into_file_and_makes_a_new_sheet_if_row_is_XLS_MAX_ROWS (void);
        void xls_add_headline_includes_a_newline(void);
        void xls_add_headline_does_nothing_if_headline_is_empty(void);
        void make_2_sheets_out_of_8_inputlines_without_headline(void);
        void make_2_sheets_out_of_8_inputlines_with_headline(void);
        void make_2x4_lines_sheets_out_of_8_inputlines_without_headline(void);
        void make_3x2_lines_sheets_out_of_4_inputlines_with_headline(void);

  //        void  (void);
    private:
    private:
        csv2xls::xls_file_t xls_file;
        dummy_workbook *test_workbook;
        void read_CSV_into(csv2xls::xls_file_t *xlsfile,int row_count, int column_count);
};

#endif
