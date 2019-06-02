#include <sstream>
#include "parseCsvFile.hpp"
#include "callback.hpp"
#include "readHeadLine.hpp"
#include "xls_workbook.hpp"
#include "conversion.h"
#include <csv.h>
namespace csv2xls
{

    std::fstream openCsvFile(InputFile const &file_name)
    {
        std::fstream csv_input(file_name.Get(),
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
    template<typename T>
    xls_file_t createCallBackData(T&& doctype, Config const &options, HeadLineType const& head_line)
    {
        xls_file_t xls_out(OutputDoc(std::forward<T>(doctype), head_line));

        xls_out.output_file_name = options.output_file_name;
        xls_out.xls_row_limit    = options.output_row_limit;
        xls_out.sheet_name       = options.xls_sheet_name;
        xls_out
            .output_file_name
            .file_number         = FileNumber(-1);

        RowAfterNewSheet(xls_out);
        return xls_out;
    }

    auto SetUpHeadLine(std::istream &csv_input, Parser const& parser, InputHasHeadLine has_had_line)
    {
        return [has_had_line, &parser, &csv_input](xls_file_t xls_out){
            if (has_had_line.Get()) {
                readHeadLine(csv_input, parser);
            }
            return xls_out;
        };
    }

    size_t ReadBuffer(std::istream &csv_input, char_buf_t &input_buffer)
    {
        csv_input.read(input_buffer.mem.get(), input_buffer.size.Get());
        return ConvertTo<size_t>(csv_input.gcount());
    }

    auto ParseBuffer(Parser const& parser, char_buf_t &input_buffer, xls_file_t &xls_out)
    {
        return [&parser, &input_buffer, &xls_out](size_t bytes_to_parse){
            return csv_parse(parser.csv_file_parser.get(),
                             input_buffer.mem.get(),
                             bytes_to_parse,
                    /* register call back function for end of csv field*/
                             csv_cb_end_of_field,
                    /* register call back function for end of csv row*/
                             csv_cb_end_of_row,
                    /* to be passed to the call back functions*/
                             &xls_out) == bytes_to_parse;
        };
    }

    auto checkParserResult(Parser const& parser)
    {
        return [&parser](bool ok){
            if(!ok)
            {
                std::cerr << "Error while parsing file: %s" << "\n"
                          << csv_strerror(csv_error(parser.csv_file_parser.get())) << "\n";
            }
        };
    }

    int DoTheHardWork(std::istream &csv_input, Parser const& parser, char_buf_t input_buffer, xls_file_t xls_out)
    {
        auto const parse_buffer = ParseBuffer(parser, input_buffer, xls_out);
        auto const warn_on_fail = checkParserResult(parser);

        while (csv_input.good())
        {
            warn_on_fail(parse_buffer(ReadBuffer(csv_input, input_buffer)));
        }
        writeIntoFile(xls_out);
        return 0;
    }

    int parseCsvFile(Config options)
    {
        if (options.exit_clean) return 0;

        auto csv_input         = openCsvFile(options.csv_file_name);
        auto const parser      = createParser(options.csv_separator);
        //auto const setHeadLine = SetUpHeadLine(csv_input, parser, options.csv_file_has_headline);
        auto const head_line = (options.csv_file_has_headline.Get())
                                ? readHeadLine(csv_input, parser)
                                : HeadLineType{};
        return DoTheHardWork(csv_input,
                             parser,
                             char_buf_t (options.input_buffer_size),
                             createCallBackData(xls_workbook(),options, head_line));
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}

    char_buf_t::char_buf_t(InputBufferSize size_)
            : size(size_)
            ,mem(std::make_unique<char[]>(ConvertTo<size_t>(size_.Get()))) {}
}
