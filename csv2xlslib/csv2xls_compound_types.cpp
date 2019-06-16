//
// Created by marcel on 5/8/19.
//
#include "csv2xls_compound_types.h"
namespace csv2xls
{
std::string toString(DigitCount digit_count, FileNumber file_number)
{
    std::stringstream numstream;
    numstream.width(digit_count.Get());
    numstream.fill('0');
    numstream << file_number;
    return numstream.str();
}

auto OutputFileName::Get(FileNumber file_number) const -> Path
{
    auto const tail = (file_number == FileNumber(0))? extension.string()
                                                    : toString(digit_count, file_number) + extension.string();
    return name_no_extension.string() + tail;
}
}
