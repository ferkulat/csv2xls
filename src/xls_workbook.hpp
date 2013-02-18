#include "workbook.hpp"
namespace xlslib_core
{
    class workbook;
    class worksheet;
}


namespace csv2xls
{

class xls_workbook:public workbook
{
public:
             xls_workbook();
    virtual ~xls_workbook();

    virtual void clear_sheet(const std::string& sheetname);
    virtual int  write_to_file(const std::string &file_name);
    virtual void label(unsigned int  row,
                       unsigned int  col,
                       const std::string& strlabel);
private:
    xlslib_core::workbook  *wbook;
    xlslib_core::worksheet *wsheet;

};
}
