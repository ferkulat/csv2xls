//
// Created by marcel on 6/10/19.
//

#ifndef CSV2XLS_CONVERTCSV_H
#define CSV2XLS_CONVERTCSV_H
#include "OutputDoc.hpp"
#include "csv2xls_types.h"

namespace csv2xls
{
struct Buffer;
struct Parameter
{
    std::optional<OutputRowLimit> output_row_limit;
    CsvSeparator     csv_separator;
    InputBufferSize input_buffer_size;
    InputHasHeadLine input_has_head_line;
};

std::optional<OutputDoc>
convertCsv(Buffer& buffer, Parameter const& parameter, std::istream& stream, std::optional<OutputDoc> output_doc);

}
#endif //CSV2XLS_CONVERTCSV_H
