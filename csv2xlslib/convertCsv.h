//
// Created by marcel on 6/10/19.
//

#ifndef CSV2XLS_CONVERTCSV_H
#define CSV2XLS_CONVERTCSV_H

#include "OutputDoc.hpp"
#include "csv2xls_types.h"
#include <fstream>
namespace csv2xls
{
struct Buffer;
struct Parameter
{
    std::optional<OutputRowLimit> output_row_limit;
    CsvSeparator     csv_separator;
};
OutputDoc
convertCsv(OutputDoc output_doc, Buffer& buffer, Parameter const& parameter, std::istream& stream);
}
#endif //CSV2XLS_CONVERTCSV_H
