//
// Created by marcel on 4/25/19.
//

#ifndef CSV2XLS_CSV2XLS_TYPES_H
#define CSV2XLS_CSV2XLS_TYPES_H

#include "SkilledType.h"
#include <checked_cmd.h>
#include <filesystem>
namespace csv2xls
{
#define TYPE_SAFE(Name, Type) using Name = CheckedCmd::CheckedCmdTypesafe::Typesafe<Type, struct TypeTag##Name>;

TYPE_SAFE(CsvSeparatorIsTab, bool)
TYPE_SAFE(InputHasHeadLine, bool)
TYPE_SAFE(PrintVersionInfo, bool)
TYPE_SAFE(CsvSeparator, char)
TYPE_SAFE(InputBufferSize, std::streamsize)
TYPE_SAFE(XlsSheetName, std::string)
TYPE_SAFE(DigitCount, std::uint8_t)
TYPE_SAFE(OutPutFile, std::filesystem::path)
TYPE_SAFE(InputFile, std::filesystem::path)

using OutPutRowLimit = skilled_type::SkilledType<std::uint32_t, struct TypeTagOutPutRowLimit,
                                                 skilled_type::Equality,
                                                 skilled_type::RelativeComparable>;

using Row = skilled_type::SkilledType<std::uint32_t, struct TypeTagRow,
                                      skilled_type::ComparableWith<OutPutRowLimit>::templ,
                                      skilled_type::Incrementable,
                                      skilled_type::Equality>;

using OutPutColumnLimit = skilled_type::SkilledType<std::uint32_t, struct TypeTagOutPutColumnLimit>;

using Column = skilled_type::SkilledType<std::uint32_t, struct TypeTagColumn,
                                         skilled_type::ComparableWith<OutPutColumnLimit>::templ,
                                         skilled_type::Incrementable,
                                         skilled_type::Equality>;

using CellContent = skilled_type::SkilledType<std::string, struct TypeTagCellContent>;
using FileNumber = skilled_type::SkilledType<int, struct TypeTagFileNumber,
                                             skilled_type::Incrementable>;
#undef TYPE_SAFE
}
#endif //CSV2XLS_CSV2XLS_TYPES_H
