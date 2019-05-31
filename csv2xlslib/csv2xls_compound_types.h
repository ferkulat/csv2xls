//
// Created by marcel on 5/8/19.
//

#ifndef CSV2XLS_CSV2XLS_COMPOUND_TYPES_H
#define CSV2XLS_CSV2XLS_COMPOUND_TYPES_H
#include "csv2xls_types.h"
#include "default_values.h"

namespace csv2xls
{
struct OutputFileName
{
    Path       name_no_extension;
    Path       extension;
    FileNumber file_number = FileNumber(0);
    DigitCount digit_count = DEFAULT_XLS_DIGIT_COUNT;
    auto       Get() const -> Path;
};
struct Config
{
    InputFile        csv_file_name;
    OutputFileName   output_file_name;
    XlsSheetName     xls_sheet_name        = XlsSheetName("Table1");
    OutputRowLimit   output_row_limit      = DEFAULT_XLS_MAX_LINES;
    InputBufferSize  input_buffer_size     = DEFAULT_CSV_BUFFER_SIZE;
    CsvSeparator     csv_separator         = DEFAULT_CSV_TAB_DELIMITER;
    InputHasHeadLine csv_file_has_headline = InputHasHeadLine(false);
    bool             exit_clean            = false;
};

} // namespace csv2xls
#endif // CSV2XLS_CSV2XLS_COMPOUND_TYPES_H
