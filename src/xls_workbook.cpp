#include "xls_workbook.hpp"
#include "xlslib.hpp"

namespace csv2xls
{

xls_workbook::
xls_workbook()
{
    this->wbook  = NULL;
    this->wsheet = NULL;
}

xls_workbook::
~xls_workbook()
{
    delete(this->wbook);
    this->wbook = NULL;
    
}

void
xls_workbook::
clear_sheet(const std::string& sheetname)
{
   if (NULL != this->wbook)
   {
       delete(this->wbook);
       this->wbook = NULL;
       
   }
   this->wbook  = new xlslib_core::workbook();
   this->wsheet = this->wbook->sheet(sheetname);
   
}

void
xls_workbook::
label(unsigned32_t row, unsigned32_t col, const std::string& strlabel)
{
    this->wsheet->label(row, col, strlabel);
}

int
xls_workbook::
write_to_file(const std::string& file_name)
{
   return wbook->Dump(file_name); 
}
}
