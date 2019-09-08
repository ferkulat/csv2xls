#ifndef PARSE_CSV_FILE_HPP
#define PARSE_CSV_FILE_HPP
#include "parsecmd.hpp"

namespace csv2xls
{
    class FileNotOpen : public std::runtime_error
    {
    public:
        explicit FileNotOpen(char const *);
    };

    int
    parseCsvFile(Config const& options);
}
#endif
