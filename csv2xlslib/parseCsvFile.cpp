#include "convertCsv.h"
#include "parseCsvFile.hpp"
#include "XlsWorkBook.hpp"
#include "conversion.h"
#include "readHeadLine.hpp"
#include "Helpers.h"
#include <sstream>
#include "readBuffer.h"
#include "funcomp.h"


namespace csv2xls
{
    auto XlsFileGenerator(Config const& config)
    {
        return[&config](){
            return XlsWorkBook(config.xls_sheet_name);
        };
    }

    auto mayReadHeadLine(Parameter parameter, std::istream& input_stream){
        std::optional<std::string> headline;
        if (parameter.input_has_head_line.Get())
        {
            std::string line;
            std::getline(input_stream, line);
            line.append("\n");
            headline = line;
        }
        return headline;
    }

    auto addHeadLineFrom(Parameter parameter, std::optional<std::string> headline, OutputDoc output_doc){
        if(headline)
        {
            std::stringstream csv_input(headline.value());
            auto buffer = Buffer(parameter.input_buffer_size);
            output_doc.set(parameter.input_has_head_line);
            return convertCsv(buffer, parameter, csv_input, std::move(output_doc));
        }
        return std::optional<OutputDoc>(std::move(output_doc));
    }


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

    enum class WriteStatus {Ok, Empty, Error};

    auto writeIntoFile (OutputFileName output_file_name_, EndlessRange<FileNumber> num_gen)
    {
        return [output_file_name= std::move(output_file_name_), num_gen_= std::move(num_gen)](std::optional<OutputDoc> output_doc){
            if (!output_doc || output_doc->isEmpty())
                return WriteStatus::Empty;

            auto const result = output_doc->writeInto(output_file_name, num_gen_());
            if(result)
                return WriteStatus::Error;

            return WriteStatus::Ok;
        };
    }

    int parseCsvStream(Config const& config, std::istream& csv_input, std::function<OutputDoc()> makeOutputDoc){
        // data
        auto       buffer    = Buffer(config.input_buffer_size);
        auto const parameter = Parameter{config.output_row_limit,
                                         config.csv_separator,
                                         config.input_buffer_size,
                                         config.csv_file_has_headline};
        auto const headLine  = mayReadHeadLine(parameter, csv_input);

        //composing functions
        using funcomp::operator|;
        using funcomp::repeatUntil;
        using std::placeholders::_1;

        auto writeFile    = writeIntoFile(config.output_file_name, EndlessRange(FileNumber(0)));
        auto convert      = std::bind(convertCsv, std::ref(buffer), parameter, std::ref(csv_input), _1);
        auto addHeadLine  = std::bind(addHeadLineFrom, parameter, headLine, _1);
        auto isEmptyOrErr = isEitherOf(WriteStatus::Empty, WriteStatus::Error);
        auto conv         = makeOutputDoc|addHeadLine|convert|writeFile|repeatUntil(isEmptyOrErr);

        return (conv() == WriteStatus::Error)? 1:0;
    }

    int parseCsvFile(Config const& config)
    {
        if (config.exit_clean) return 0;

        auto csv_input = openCsvFile(config.csv_file_name);
        auto makeOutputDoc=[](auto file_gen ) {
                return [file_gen](){
                    return OutputDoc(file_gen());
                };
        };

        return parseCsvStream(config, csv_input, makeOutputDoc(XlsFileGenerator(config)));
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}

}
