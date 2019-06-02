#include <iostream>
#include "readHeadLine.hpp"
#include "callback.hpp"
#include <csv.h>

namespace csv2xls
{
HeadLineType readHeadLine( std::istream &csv_input,
                    Parser const& csv_in)
{
    HeadLineType head_line;
    std::string head_line_buffer;
    if (!getline(csv_input, head_line_buffer).fail())
    {
        //getline omits newline from input stream
        // but csv_parser needs it
        head_line_buffer.append("\n");

        if (csv_parse(csv_in.csv_file_parser.get(), head_line_buffer.c_str(),
                head_line_buffer.size(),
                /* register call back function for end of csv field*/
                csv_cb_headline_field,
                /* register call back function for end of csv row*/
                      nullptr,
                /* to be passed to the call back functions*/
                &head_line) != head_line_buffer.size())
        {
            std::cerr << "Error while parsing file: %s" << "\n"
                    << csv_strerror(csv_error(csv_in.csv_file_parser.get())) << "\n";
            exit(EXIT_FAILURE);
        }
    }
    return head_line;

}
}
