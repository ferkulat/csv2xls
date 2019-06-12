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

    struct Given_a_Csv_file_with_3_lines_and_no_newline_at_end_of_file
    {
        std::stringstream file;
        std::vector<std::vector<std::string>> data;

        Given_a_Csv_file_with_3_lines_and_no_newline_at_end_of_file()
        {
            file << "1111;2222;3333\n";
            file << "dog;cat;duck\n";
            file << "milk;tea;coffee";
        }
    };
    TEST_CASE_METHOD(Given_a_Csv_file_with_3_lines_and_no_newline_at_end_of_file, "and a row limit of 2")
    {
        Buffer buffer(1024);
        auto outfile = OutFile(OutputRowLimit(2), OutputColumnLimit(4),data);
        auto const actual = convertCsv(OutputDoc(OutFile(outfile)), buffer, OutputRowLimit(2), file);
        REQUIRE(data.size() == 2 );
        REQUIRE(data[0].size() == 3);
        REQUIRE(data[1].size() == 3);
    }

    TEST_CASE_METHOD(Given_a_Csv_file_with_3_lines_and_no_newline_at_end_of_file, "and a row limit of 3")
    {
        Buffer buffer(10);
        auto outfile = OutFile(OutputRowLimit(3), OutputColumnLimit(4),data);
        auto const actual = convertCsv(OutputDoc(OutFile(outfile)), buffer, OutputRowLimit(3), file);
        REQUIRE(data.size() == 3 );
        using ROW = std::vector<std::string>;
        REQUIRE(data[0] == ROW{"1111","2222","3333"});
        REQUIRE(data[1] == ROW{"dog","cat","duck"});
        REQUIRE(data[2] == ROW{"milk","tea","coffee"});

    }
}
}