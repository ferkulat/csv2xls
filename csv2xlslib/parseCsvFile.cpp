#include "parseCsvFile.hpp"
#include "XlsWorkBook.hpp"
#include "conversion.h"
#include "readHeadLine.hpp"
#include "Helpers.h"
#include <sstream>
#include "convertCsv.h"
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
    auto mayReadHeadLine(Parameter parameter, std::fstream& input_stream){
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
    auto addHeadLineFrom(Parameter parameter, std::optional<std::string> headline_to_move){
        return [headline   = std::move(headline_to_move),
                parameter_ = std::move(parameter)
               ](OutputDoc output_doc){

            if(headline)
            {
                std::stringstream csv_input(headline.value());
                auto buffer = Buffer(parameter_.input_buffer_size);
                output_doc.set(parameter_.input_has_head_line);
                return convertCsv(buffer, parameter_, csv_input, std::move(output_doc));
            }
            return std::optional<OutputDoc>(std::move(output_doc));
        };
    }
    auto makeOutputDoc=[](auto file_gen ) {
            return OutputDoc(file_gen());
    };

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

    auto writeIntoFile (OutputFileName output_file_name, EndlessRange<FileNumber> num_gen)
    {
        return [=](std::optional<OutputDoc> output_doc){
            if (!output_doc || output_doc->isEmpty())
                return WriteStatus::Empty;

            auto const result = output_doc->writeInto(output_file_name, num_gen());
            if(result)
                return WriteStatus::Error;

            return WriteStatus::Ok;
        };
    }

    int parseCsvFile(Config const& config)
    {
        using funcomp::operator|;
        using funcomp::repeatUntil;

        if (config.exit_clean) return 0;

        auto const parameter = Parameter{config.output_row_limit,
                                         config.csv_separator,
                                         config.input_buffer_size,
                                         config.csv_file_has_headline};

        auto csv_input    = openCsvFile(config.csv_file_name);
        auto buffer       = Buffer(config.input_buffer_size);
        auto headLine     = mayReadHeadLine(parameter, csv_input);
        auto writeFile    = writeIntoFile(config.output_file_name, EndlessRange(FileNumber(0)));
        auto convert      = std::bind(convertCsv, std::ref(buffer), parameter, std::ref(csv_input), std::placeholders::_1);
        auto addHeadLine  = addHeadLineFrom(parameter, headLine);
        auto isEmptyOrErr = isEitherOf(WriteStatus::Empty, WriteStatus::Error);
        auto convertWith  = makeOutputDoc|addHeadLine|convert|writeFile|repeatUntil(isEmptyOrErr);

        return (convertWith(XlsFileGenerator(config)) == WriteStatus::Error)? 1:0;
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}

}
