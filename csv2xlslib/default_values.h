#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

#include <climits>

namespace csv2xls
{
    constexpr char CHAR_TABULATOR            = 9;
    constexpr char CHAR_SEMICOLON            = 59;
    constexpr char DEFAULT_CSV_TAB_DELIMITER = CHAR_SEMICOLON;
    constexpr auto DEFAULT_XLS_SHEET_NAME    = "Table1";

    constexpr unsigned long DEFAULT_XLS_MAX_LINES   = 65536;
    constexpr unsigned long DEFAULT_CSV_BUFFER_SIZE = 1024*1024;
    constexpr unsigned long MAX_CSV_BUFFER_SIZE     = ULONG_MAX;
    constexpr unsigned long DEFAULT_XLS_DIGIT_COUNT = 4;
    constexpr unsigned long MAX_XLS_DIGIT_COUNT     = 10;
}

#endif
