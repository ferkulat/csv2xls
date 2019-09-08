//
// Created by marcel on 9/8/19.
//
#include "parseCsvStream.hpp"
#include "Helpers.h"
#include "convertCsv.h"
#include "funcomp.h"
#include "readBuffer.h"
namespace csv2xls
{
auto mayReadHeadLine(Parameter parameter, std::istream& input_stream)
{
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

auto addHeadLineFrom(Parameter parameter, std::optional<std::string> headline, OutputDoc output_doc)
{
    if (headline)
    {
        auto buffer = Buffer(parameter.input_buffer_size);
        std::stringstream csv_input(headline.value());
        output_doc.set(parameter.input_has_head_line);
        return convertCsv(buffer, parameter, csv_input, std::move(output_doc));
    }
    return std::optional<OutputDoc>(std::move(output_doc));
}

enum class WriteStatus
{
    Ok,
    Empty,
    Error
};

auto writeIntoFile(OutputFileName output_file_name, EndlessRange<FileNumber> const& num_gen,
                   std::optional<OutputDoc> output_doc)
{
    if (!output_doc || output_doc->isEmpty())
        return WriteStatus::Empty;

    auto const result = output_doc->writeInto(output_file_name, num_gen());
    if (result)
        return WriteStatus::Error;

    return WriteStatus::Ok;
}

int parseCsvStream(Config const& config, std::istream& csv_input, std::function<OutputDoc()> makeOutputDoc)
{
    // data
    auto       buffer    = Buffer(config.input_buffer_size);
    auto const parameter = Parameter{config.output_row_limit, config.csv_separator, config.input_buffer_size,
                                     config.csv_file_has_headline};
    auto const headLine  = mayReadHeadLine(parameter, csv_input);

    // composing functions
    using funcomp::operator|;
    using funcomp::repeatUntil;
    using std::placeholders::_1;

    // For chaining functions, functions need to take one parameter only
    auto writeFile    = std::bind(writeIntoFile, config.output_file_name, EndlessRange(FileNumber(0)), _1);
    auto convert      = std::bind(convertCsv, std::ref(buffer), parameter, std::ref(csv_input), _1);
    auto addHeadLine  = std::bind(addHeadLineFrom, parameter, headLine, _1);
    auto isEmptyOrErr = isEitherOf(WriteStatus::Empty, WriteStatus::Error);

    auto convertCsvToOutputDoc = makeOutputDoc | addHeadLine | convert | writeFile | repeatUntil(isEmptyOrErr);

    return (convertCsvToOutputDoc() == WriteStatus::Error) ? 1 : 0;
}
} // namespace csv2xls
