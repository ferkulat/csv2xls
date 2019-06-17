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

    template<typename NumGen>
    auto writeIntoFile (OutputFileName output_file_name, NumGen num_gen)
    {
        return [=](OutputDoc output_doc){
            if(output_doc.isEmpty())
                return WriteStatus::Empty;

            auto const result = output_doc.writeInto(output_file_name, num_gen());
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

        auto const parameter = Parameter{config.output_row_limit, config.csv_separator};

        auto csv_input    = openCsvFile(config.csv_file_name);
        auto buffer       = Buffer(config.input_buffer_size);
        auto writeFile    = writeIntoFile(config.output_file_name, EndlessRange(FileNumber(0)));
        auto convert      = [&](OutputDoc output_doc){
                               return convertCsv(buffer, parameter, csv_input, std::move(output_doc));
                            };
        auto csv2doc      = makeOutputDoc|convert;
        auto isEmptyOrErr = isEitherOf(WriteStatus::Empty, WriteStatus::Error);
        auto convertWith  = csv2doc|writeFile|repeatUntil(isEmptyOrErr);

        return (convertWith(XlsFileGenerator(config)) == WriteStatus::Error)? 1:0;
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}

    char_buf_t::char_buf_t(InputBufferSize size_)
            : size(size_)
            ,mem(std::make_unique<char[]>(ConvertTo<size_t>(size_.Get()))) {}
}
