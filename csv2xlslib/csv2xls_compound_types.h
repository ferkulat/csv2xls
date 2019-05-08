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
}
#endif //CSV2XLS_CSV2XLS_COMPOUND_TYPES_H
