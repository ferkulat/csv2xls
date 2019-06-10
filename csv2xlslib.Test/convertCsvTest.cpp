//
// Created by marcel on 6/10/19.
//

#include "catch.hpp"
#include <convertCsv.h>
#include <csv2xls_compound_types.h>
#include <readBuffer.h>
#include <sstream>
namespace csv2xls
{
namespace ConvertCsvTest{

    struct OutFile
    {
        OutFile(OutputRowLimit output_row_limit_, OutputColumnLimit output_column_limit_, std::vector<std::vector<std::string>>& data_)
            : output_column_limit(output_column_limit_)
            , output_row_limit(output_row_limit_)
            , data(data_)
        {
        }
        void clearSheet(){
            //data.clear();
        };

        int writeInto(OutputFileName const& /*output_file_name*/){return 1;}

        void setCell( Row row, Column column,
                      CellContent cell_content)
        {
            if(data.size() < row.Get()+1)
                data.resize(row.Get()+1);
            auto &current_row = data.at(row.Get());

            if(current_row.size() < column.Get()+1)
                current_row.resize(column.Get()+1);

            current_row.at(column.Get()) = std::string(cell_content.start, cell_content.length);
        }
        auto columnLimit()-> std::optional<OutputColumnLimit>
        {
            return output_column_limit;
        }
        OutputColumnLimit output_column_limit;
        OutputRowLimit output_row_limit;
        std::vector<std::vector<std::string>>& data;
    };

    TEST_CASE("lol")
    {
        std::stringstream file;
        file << "1   ;2  ;  3 \n";
        file << "dog ;cat;duck\n";
        file << "milk;tea;coffee";
        std::vector<std::vector<std::string>> data;
        Buffer buffer(1024);
        auto outfile = OutFile(OutputRowLimit(2), OutputColumnLimit(4),data);
        auto const actual = convertCsv(OutputDoc(OutFile(outfile)), buffer, OutputRowLimit(2), file);
        REQUIRE(data.size() == 2 );
    }

}
}