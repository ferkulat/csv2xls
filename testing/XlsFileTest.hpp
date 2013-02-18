// Datei: filenameTest.hpp
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

  //        void  (void);
    private:
    private:
        csv2xls::xls_file_t xls_file;
        dummy_workbook *test_workbook;
};

#endif
