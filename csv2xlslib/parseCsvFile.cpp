#include "parseCsvFile.hpp"
#include "XlsWorkBook.hpp"
#include "conversion.h"
#include "readHeadLine.hpp"
#include <csv.h>
#include "Helpers.h"
#include <sstream>
#include "convertCsv.h"
#include "readBuffer.h"
#include "funcomp.h"


namespace csv2xls
{

    auto OutFileGenerator(Config const& config)
    {
        return[&](){
            return XlsWorkBook(config.xls_sheet_name);
        };
    }

    template<typename NumberGen>
    auto makeOutputDoc(NumberGen number_gen)
    {
        return [num_gen = std::move(number_gen)](Config const& config){
            return OutputDoc(OutFileGenerator(config)(), num_gen());
        };
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

    auto writeIntoFile (OutputFileName output_file_name)
    {
        return [=](OutputDoc output_doc){
            if(output_doc.isEmpty())
                return WriteStatus::Empty;

            auto const result = output_doc.writeInto(output_file_name);
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
        auto       csv_input = openCsvFile(config.csv_file_name);
        auto       buffer    = Buffer(config.input_buffer_size);
        auto       convert   = [&](OutputDoc output_doc){
                                    return convertCsv(buffer, parameter,csv_input,std::move(output_doc));
                                };
        auto convertWith     = makeOutputDoc(EndlessRange(FileNumber(0)))
                                |convert
                                |writeIntoFile(config.output_file_name)
                                |repeatUntil(isEitherOf(WriteStatus::Empty, WriteStatus::Error))
                                ;


        return (convertWith(config) == WriteStatus::Error)? 1:0;
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}

    char_buf_t::char_buf_t(InputBufferSize size_)
            : size(size_)
            ,mem(std::make_unique<char[]>(ConvertTo<size_t>(size_.Get()))) {}
}
