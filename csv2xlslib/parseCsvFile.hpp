#ifndef PARSE_CSV_FILE_HPP
#define PARSE_CSV_FILE_HPP
#include <iostream>
#include <fstream>
#include "XlsFile.hpp"
#include "parsecmd.hpp"
#include "csv.hpp"
namespace csv2xls
{

void
parseCsvFile(std::fstream &csv_input,
             csv_file_t &csv_in,
             xls_file_t &xls_out,
             opts_t &options);

}
#endif
