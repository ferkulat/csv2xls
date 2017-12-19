#include <unordered_map>
#include <sstream>
#include "parseCsvFile.hpp"
#include "callback.hpp"
#include "readHeadLine.hpp"
#include "xls_workbook.hpp"
#include "parsecmd.hpp"

namespace csv2xls
{
    struct char_buf_t
    {
        char_buf_t(size_t size)
                :size(size)
                 ,mem(std::make_unique<char[]>(size)) {}
        size_t size; /**< number of bytes [to allocate|allocated]*/
        std::unique_ptr<char[]> mem; /**< pointer to allocated memory*/
    } ;

    std::fstream openCsvFile(std::string const &file_name)
    {
        std::fstream csv_input(file_name.c_str(),
                               std::ifstream::in | std::ifstream::binary);
        if (!csv_input.is_open())
        {
            std::stringstream ss;
            ss << "Failed to open file ";
            ss << file_name << "\n";
            throw FileNotOpen( ss.str().c_str() );
        }
        return csv_input;
    }

    xls_file_t createCallBackData(opts_t const &options)
    {
        xls_file_t xls_out;

        xls_out.filename      = options.xls_file_name;
        xls_out.xls_row_limit = options.xls_row_limit;
        xls_out.sheet_name    = options.xls_sheet_name;
        xls_out.digit_count   = options.xls_digit_count;
        xls_out.wbook         = std::make_unique<xls_workbook>();
        xls_out.page_number   = -1;

        xls_new_sheet(&xls_out);
        return xls_out;
    }

    auto SetUpHeadLine(std::fstream &csv_input, Parser const& parser, bool has_had_line)
    {
        return [has_had_line, &parser, &csv_input](xls_file_t xls_out){
            if (has_had_line) {
                readHeadLine(csv_input, parser, xls_out);
            }
            return xls_out;
        };
    }

    int DoTheHardWork(std::fstream &csv_input, Parser const& parser, char_buf_t input_buffer, xls_file_t xls_out)
    {
        unsigned long bytes_read;

        while (csv_input.good())
        {
            csv_input.read(input_buffer.mem.get(), input_buffer.size);
            bytes_read = csv_input.gcount();

            if (csv_parse(parser.csv_file_parser.get(), input_buffer.mem.get(), bytes_read,
                    /* register call back function for end of csv field*/
                          csv_cb_end_of_field,
                    /* register call back function for end of csv row*/
                          csv_cb_end_of_row,
                    /* to be passed to the call back functions*/
                          &xls_out) != bytes_read)
            {
                std::cerr << "Error while parsing file: %s" << "\n"
                          << csv_strerror(csv_error(parser.csv_file_parser.get())) << "\n";
            }
        }
        xls_dump_worksheet(&xls_out);
        return 0;
    }

    int parseCsvFile(opts_t options)
    {
        if (options.exit_clean) return 0;

        auto csv_input           = openCsvFile(options.csv_file_name);
        auto const parser        = createParser(options.csv_tab_delimiter);
        auto const set_head_line = SetUpHeadLine(csv_input, parser, options.csv_file_has_headline);

        return DoTheHardWork(csv_input,
                             parser,
                             char_buf_t (options.input_buffer_size),
                             set_head_line(createCallBackData(options)));
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}
}
