#ifndef READHEADLINE_HPP 
#define READHEADLINE_HPP 
#include <fstream>
#include "parsecmd.hpp"
#include "XlsFile.hpp"

#include "csv.hpp"
namespace csv2xls
{
    HeadLineType readHeadLine(std::istream &csv_input,
                  Parser const& csv_in);
}
#endif
