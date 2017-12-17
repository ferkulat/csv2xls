#ifndef READHEADLINE_HPP 
#define READHEADLINE_HPP 
#include <fstream>
#include "parsecmd.hpp"
#include "XlsFile.hpp"

#include "csv.hpp"
namespace csv2xls
{
void readHeadLine(std::fstream &csv_input,
                  csv_file_t &csv_in,
                  xls_file_t &xls_out);
}
#endif
