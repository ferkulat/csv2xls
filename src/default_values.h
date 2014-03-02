#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H

namespace csv2xls

{
#include <limits.h>

#define DEFAULT_XLS_MAX_LINES     65536
#define DEFAULT_CSV_TAB_DELIMITER 59 /** ';' */
#define DEFAULT_CSV_BUFFER_SIZE   1024*1024
#define MAX_CSV_BUFFER_SIZE       ULONG_MAX
#define DEFAULT_XLS_DIGIT_COUNT   4
#define MAX_XLS_DIGIT_COUNT       10
#define DEFAULT_XLS_SHEET_NAME    "Table1"
}

#endif
