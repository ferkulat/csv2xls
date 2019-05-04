#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

#include <limits>
#include "csv2xls_types.h"

namespace csv2xls
{
    constexpr char CHAR_TABULATOR            = 9;
    constexpr char CHAR_SEMICOLON            = 59;
    constexpr auto DEFAULT_CSV_TAB_DELIMITER = CsvSeparator(CHAR_SEMICOLON);
    constexpr auto DEFAULT_XLS_MAX_LINES     = OutPutRowLimit(65536);
    constexpr auto DEFAULT_XLS_MIN_LINES     = OutPutRowLimit(1);
    constexpr auto DEFAULT_CSV_BUFFER_SIZE   = InputBufferSize(1024*1024);
    constexpr auto MAX_CSV_BUFFER_SIZE       = InputBufferSize(std::numeric_limits<InputBufferSize::type>::max());
    constexpr auto MIN_CSV_BUFFER_SIZE       = InputBufferSize(1);
    constexpr auto DEFAULT_XLS_DIGIT_COUNT   = OutPutFileNameDigitCount(4);
    constexpr auto MAX_XLS_DIGIT_COUNT       = OutPutFileNameDigitCount(10);
}

#endif
