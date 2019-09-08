#include "parseCsvFile.hpp"
#include "XlsWorkBook.hpp"
#include "parseCsvStream.hpp"
#include <fstream>
#include <sstream>

namespace csv2xls
{
    auto XlsFileGenerator(Config const& config)
    {
        return[&config](){
            return XlsWorkBook(config.xls_sheet_name);
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


    auto makeOutputDoc=[](auto file_gen ) {
        return [file_gen](){
            return OutputDoc(file_gen());
        };
    };

    int parseCsvFile(Config const& config)
    {
        if (config.exit_clean) return 0;

        auto csv_input = openCsvFile(config.csv_file_name);
        return parseCsvStream(config, csv_input, makeOutputDoc(XlsFileGenerator(config)));
    }

    FileNotOpen::FileNotOpen(char const *what)
            : runtime_error(what) {}
}