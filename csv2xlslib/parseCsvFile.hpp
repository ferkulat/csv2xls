#ifndef PARSE_CSV_FILE_HPP
#define PARSE_CSV_FILE_HPP
#include "OutputDoc.hpp"
#include "parsecmd.hpp"

namespace csv2xls
{
    struct Parser;
    struct char_buf_t
    {
        explicit char_buf_t(InputBufferSize size);
        InputBufferSize size;
        std::unique_ptr<char[]> mem;
    } ;

    class FileNotOpen : public std::runtime_error
    {
    public:
        explicit FileNotOpen(char const *);
    };

    int
    parseCsvFile(Config const& options);

    int
    parseCsvStream(Config const& config, std::istream& csv_input, std::function<OutputDoc()> makeOutputDoc);

}
#endif
