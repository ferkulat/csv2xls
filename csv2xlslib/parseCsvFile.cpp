#include "parseCsvFile.hpp"
#include "XlsWorkBook.hpp"
#include "callback.hpp"
#include "conversion.h"
#include "readHeadLine.hpp"
#include <csv.h>
#include <sstream>
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

    xls_file_t createCallBackData(OutputDoc doctype, Config const &options)
    {
        xls_file_t xls_out(std::move(doctype));

        xls_out.output_file_name = options.output_file_name;
        xls_out.xls_row_limit    = options.output_row_limit;
        xls_out
            .output_file_name
            .file_number         = FileNumber(-1);

        RowAfterNewSheet(xls_out);
        return xls_out;
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

    int parseCsvStream(Config const& config, std::istream& csv_stream, OutputDoc output_doc)
    {
        auto const parser    = createParser(config.csv_separator);
        if (config.csv_file_has_headline.Get())
        {
            output_doc.setHeadLine(readHeadLine(csv_stream, parser));
        }

        return DoTheHardWork(csv_stream,
                             parser,
                             char_buf_t (config.input_buffer_size),
                             createCallBackData(std::move(output_doc), config));
    }
    int parseCsvFile(Config const& config)
    {
        if (config.exit_clean) return 0;

        auto csv_input = openCsvFile(config.csv_file_name);

        return parseCsvStream(config, csv_input, OutputDoc(XlsWorkBook(config.xls_sheet_name)));
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}

    char_buf_t::char_buf_t(InputBufferSize size_)
            : size(size_)
            ,mem(std::make_unique<char[]>(ConvertTo<size_t>(size_.Get()))) {}
}
