#ifndef PARSE_CSV_FILE_HPP
#define PARSE_CSV_FILE_HPP
#include <iostream>
#include <fstream>
#include "XlsFile.hpp"
#include "parsecmd.hpp"
#include "csv.hpp"
namespace csv2xls
{

    class FileNotOpen : public std::runtime_error
    {
    public:
        FileNotOpen(char const *);

    };
int
parseCsvFile(opts_t options);

}
#endif
