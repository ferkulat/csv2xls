//
// Created by marcel on 6/2/19.
//
#include "TestHelper.h"
#include <catch.hpp>
#include <parseCsvStream.hpp>
#include "OutputDoc.hpp"
namespace csv2xls
{
namespace parseCsvStreamTest
{
std::string createCSV(Row row_count, Column column_count)
{
    auto result = std::string();

    auto cell = std::string("lol");

    for (auto row = Row(0); row < row_count; row++)
    {
        result.append(std::to_string(row.Get()) + ",0");
        for (auto col = Column(1); col < column_count; col++)
        {
            result.append(";" + std::to_string(row.Get()) + "," + std::to_string(col.Get()));
        }
        result.append("\n");
    }
    return result;
}

auto makeTestOutputFile(std::shared_ptr<Testing::DummyWorkBook>& test_workbook){
    return [&](){return OutputDoc(Testing::WrapperWorkBook(test_workbook));};
}

struct Given_an_input_file_without_headline
{
    std::shared_ptr<Testing::DummyWorkBook> test_workbook = std::make_shared<Testing::DummyWorkBook>();
    Config                                  config;
    Given_an_input_file_without_headline()
    {
        config.xls_sheet_name        = XlsSheetName("testsheet");
        config.csv_file_has_headline = InputHasHeadLine(false);
        config.csv_file_name         = InputFile("lol");
        config.output_row_limit      = OutputRowLimit(3);
    }

    virtual ~Given_an_input_file_without_headline() = default;
};

struct Given_an_input_file_with_headline
{
    std::shared_ptr<Testing::DummyWorkBook> test_workbook = std::make_shared<Testing::DummyWorkBook>();
    Config                                  config;
    Given_an_input_file_with_headline()
    {
        config.xls_sheet_name        = XlsSheetName("testsheet");
        config.csv_file_has_headline = InputHasHeadLine(true);
        config.csv_file_name         = InputFile("lol");
        config.output_row_limit      = OutputRowLimit(3);
    }

    virtual ~Given_an_input_file_with_headline() = default;
};

TEST_CASE_METHOD(Given_an_input_file_without_headline,
                 " with 8 lines and line limit of 3 then 3 files will be produced")
{
    auto const        csv_file = createCSV(Row(8), Column(3));
    std::stringstream csv_stream(csv_file);
    parseCsvStream(config, csv_stream, makeTestOutputFile(test_workbook));

    REQUIRE(3 == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Given_an_input_file_with_headline,
" with 8 lines and line limit of 3 then 4 files will be produced")
{
    auto const        csv_file = createCSV(Row(8), Column(3));
    std::stringstream csv_stream(csv_file);
    parseCsvStream(config, csv_stream, makeTestOutputFile(test_workbook));

    REQUIRE(4 == test_workbook->called_write_to_file);
}

TEST_CASE_METHOD(Given_an_input_file_with_headline,
" with quoted cells and 8 lines and line limit of 3 then 4 files will be produced")
{
    auto const csv_file =  std::string(R"("col1";"col2";"col3")") + "\n"
                         + std::string(R"("1";"2";"3")")          + "\n"
                         + std::string(R"("4";"5";"6")")          + "\n";

    std::stringstream csv_stream(csv_file);
    parseCsvStream(config, csv_stream, makeTestOutputFile(test_workbook));

    REQUIRE(1 == test_workbook->files.size());
    REQUIRE(3 == test_workbook->files[0].size());
}

TEST_CASE_METHOD(Given_an_input_file_with_headline,
" with quoted empty cells and 8 lines and line limit of 3 then 4 files will be produced")
{
    config.input_buffer_size = InputBufferSize(10);
    auto const csv_file      =  std::string(R"("col1";"col2";"col3")") + "\n"
                              + std::string(R"("1";"2";"3")")          + "\n"
                              + std::string(R"("4";"";"6")")           + "\n";

    std::stringstream csv_stream(csv_file);
    parseCsvStream(config, csv_stream, makeTestOutputFile(test_workbook));

    REQUIRE(1 == test_workbook->files.size());
    REQUIRE(3 == test_workbook->files[0].size());
}

}
}
