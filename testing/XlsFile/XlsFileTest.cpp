#include "XlsFileTest.hpp"
#include "CppUTest/TestHarness.h"

using namespace std;



TEST_GROUP(Group1)
{
       csv2xls::xls_file_t xls_file;
        dummy_workbook *test_workbook;


   void setup()
   {
        test_workbook           = new dummy_workbook();
        xls_file.wbook          = test_workbook;
        xls_file.filename       = "file";
        xls_file.xls_row_limit  = XLS_MAX_ROWS;
        xls_file.current_column = 0;
        xls_file.current_row    = 0;


      // Init stuff
   }

   void teardown()
   {
    delete xls_file.wbook;
      // Uninit stuff
   }	
};


TEST(Group1,xls_append_cell_increases_column)
{
    xls_file.current_column = 0;
    xls_file.current_row = 0;
    csv2xls::xls_append_cell(&xls_file,"lol");
    LONGS_EQUAL ( 0, xls_file.current_row );
    LONGS_EQUAL ( 1, xls_file.current_column );
}


TEST(Group1,xls_append_cell_ignores_columns_greater_than_XLS_MAX_COLUMNS )
{
    xls_file.current_column = XLS_MAX_COLUMNS ;
    xls_file.current_row = 0;
    csv2xls::xls_append_cell(&xls_file,"lol");
    LONGS_EQUAL ( 0,               xls_file.current_row    );
    LONGS_EQUAL ( XLS_MAX_COLUMNS, xls_file.current_column );
}

TEST(Group1,xls_newline_increases_row )
{
    xls_file.current_column = 0;
    xls_file.current_row = 0;
    csv2xls::xls_newline(&xls_file);
    LONGS_EQUAL ( 0, xls_file.current_column );
    LONGS_EQUAL ( 1, xls_file.current_row );
    LONGS_EQUAL ( 0, test_workbook->called_clear_sheet );
    LONGS_EQUAL ( 0, test_workbook->called_write_to_file );

}


TEST(Group1,xls_newline_writes_sheet_into_file_and_makes_a_new_sheet_if_row_is_XLS_MAX_ROWS )
{
    xls_file.current_column = 2;
    xls_file.current_row = XLS_MAX_ROWS;
    csv2xls::xls_newline(&xls_file);
    CHECK ( 1 == test_workbook->called_clear_sheet );
    CHECK ( 1 == test_workbook->called_write_to_file );
    CHECK ( 0 == xls_file.current_column );
    CHECK ( 0 == xls_file.current_row );

}


TEST(Group1,xls_add_headline_does_nothing_if_headline_is_empty)
{
    xls_file.headline.clear();
    csv2xls::xls_add_headline(&xls_file);
    CHECK ( 0 == test_workbook->called_clear_sheet );
    CHECK ( 0 == test_workbook->called_label );
    CHECK ( 0 == test_workbook->called_write_to_file );
    CHECK ( 0 == xls_file.current_column );
    CHECK ( 0 == xls_file.current_row );
}


TEST(Group1,xls_add_headline_includes_a_newline)
{
    std::vector<string>tmp(4,"lol");
    xls_file.headline = tmp;
    csv2xls::xls_add_headline(&xls_file);
    CHECK ( 0 == test_workbook->called_clear_sheet );
    CHECK ( 4 == test_workbook->called_label );
    CHECK ( 0 == test_workbook->called_write_to_file );
    CHECK ( 0 == xls_file.current_column );
    CHECK ( 1 == xls_file.current_row );
}


TEST(Group1,make_2_sheets_out_of_8_inputlines_without_headline)
{
    #define INPUT_COLUMNS        3
    #define INPUT_ROWS           8
    #define LINE_LIMIT_PER_SHEET 5

    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;
    read_CSV_into(&xls_file,INPUT_ROWS,INPUT_COLUMNS);
    
    CHECK ( 1 == test_workbook->called_clear_sheet );
    CHECK ( INPUT_ROWS * INPUT_COLUMNS == test_workbook->called_label );
    CHECK ( 1 == test_workbook->called_write_to_file );
    CHECK ( 0 == xls_file.current_column );

    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef LINE_LIMIT_PER_SHEET
}


TEST(Group1,make_2_sheets_out_of_8_inputlines_with_headline)
{
    #define INPUT_COLUMNS         3
    #define INPUT_ROWS            8
    #define HEADLINE              1
    #define LINE_LIMIT_PER_SHEET  5

    std::vector<string>tmp(INPUT_COLUMNS,"head");
    xls_file.headline = tmp;
    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;

    read_CSV_into(&xls_file,INPUT_ROWS,INPUT_COLUMNS);
    CHECK (  1 == test_workbook->called_clear_sheet );
    CHECK ( (INPUT_ROWS + HEADLINE)* INPUT_COLUMNS
                        == test_workbook->called_label );

    CHECK (  1 == test_workbook->called_write_to_file );
    CHECK (  0 == xls_file.current_column );
    CHECK (  INPUT_ROWS + HEADLINE - LINE_LIMIT_PER_SHEET
                        == xls_file.current_row );
    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef HEADLINE
    #undef LINE_LIMIT_PER_SHEET
}


TEST(Group1,make_2x4_lines_sheets_out_of_8_inputlines_without_headline)
{
    #define INPUT_COLUMNS        3
    #define INPUT_ROWS           8
    #define LINE_LIMIT_PER_SHEET 4

    xls_file.xls_row_limit  = LINE_LIMIT_PER_SHEET;
    read_CSV_into(&xls_file,INPUT_ROWS,INPUT_COLUMNS);
    csv2xls::xls_dump_worksheet(&xls_file);

    CHECK ( 2 == test_workbook->called_write_to_file );

    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef LINE_LIMIT_PER_SHEET
}


TEST(Group1,make_3x2_lines_sheets_out_of_4_inputlines_with_headline)
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

    CHECK ( 3 == test_workbook->called_write_to_file );

    #undef INPUT_COLUMNS
    #undef INPUT_ROWS
    #undef HEADLINE
    #undef LINE_LIMIT_PER_SHEET

}


void 
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

