#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

#include <limits>

namespace csv2xls
{
    constexpr char CHAR_TABULATOR            = 9;
    constexpr char CHAR_SEMICOLON            = 59;
    constexpr unsigned char DEFAULT_CSV_TAB_DELIMITER = CHAR_SEMICOLON;
    constexpr auto DEFAULT_XLS_SHEET_NAME    = "Table1";

    constexpr int DEFAULT_XLS_MAX_LINES   = 65536;
    constexpr int DEFAULT_CSV_BUFFER_SIZE = 1024*1024;
    constexpr int MAX_CSV_BUFFER_SIZE     = std::numeric_limits<decltype(MAX_CSV_BUFFER_SIZE)>::max();
    constexpr int DEFAULT_XLS_DIGIT_COUNT = 4;
    constexpr int MAX_XLS_DIGIT_COUNT     = 10;
}

#endif
