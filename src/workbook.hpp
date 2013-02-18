/* 
 * File:   workbook.hpp
 * Author: eagle
 *
 * Created on 10. Februar 2013, 17:15
 */

#ifndef WORKBOOK_HPP
#define	WORKBOOK_HPP
#include <string>
//#include <common/xlstypes.h>

namespace csv2xls
{

class workbook
{
public:
             workbook(){};
    virtual ~workbook(){};
    
    virtual void clear_sheet(const std::string& sheetname)= 0;
    virtual int  write_to_file(const std::string &file_name) = 0;
    virtual void label(unsigned int row,
                       unsigned int col,
                       const std::string& strlabel) = 0;
};

}
#endif	/* WORKBOOK_H */

