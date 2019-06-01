//
// Created by marcel on 4/25/19.
//

#ifndef CSV2XLS_CSV2XLS_TYPES_H
#define CSV2XLS_CSV2XLS_TYPES_H

#include <Skills.h>
#include <checked_cmd.h>
#include <filesystem>
#include <csv2xls_skills.h>
namespace csv2xls
{
using Path = std::filesystem::path;

#define TYPE_SAFE(Name, Type) using Name = CheckedCmd::CheckedCmdTypesafe::Typesafe<Type, struct TypeTag##Name>;

TYPE_SAFE(CsvSeparatorIsTab, bool)
TYPE_SAFE(InputHasHeadLine, bool)
TYPE_SAFE(PrintVersionInfo, bool)
TYPE_SAFE(CsvSeparator, char)
TYPE_SAFE(InputBufferSize, std::streamsize)
TYPE_SAFE(XlsSheetName, std::string)
TYPE_SAFE(DigitCount, std::uint8_t)
TYPE_SAFE(InputFile, Path)

using OutputRowLimit = skilled_type::SkilledType<std::uint32_t, struct TypeTagOutPutRowLimit,
                                                 skilled_type::Equality,
                                                 skilled_type::Relativity>;

using Row = skilled_type::SkilledType<std::uint32_t, struct TypeTagRow,
                                      ComparableWith<OutputRowLimit>::templ,
                                      skilled_type::Incrementability,
                                      skilled_type::Equality,
                                      skilled_type::Relativity>;

using OutPutColumnLimit = skilled_type::SkilledType<std::uint32_t, struct TypeTagOutPutColumnLimit>;

using Column = skilled_type::SkilledType<std::uint32_t, struct TypeTagColumn,
                                         ComparableWith<OutPutColumnLimit>::templ,
                                         skilled_type::Incrementability,
                                         skilled_type::Equality>;

struct CellContent{
    CellContent(char const* start_, size_t length_)
    :start(start_)
    , length(length_)
    {}
    char const* start;
    size_t length;
};
using FileNumber = skilled_type::SkilledType<int, struct TypeTagFileNumber,
                                             skilled_type::Incrementability,
                                             skilled_type::Equality>;

#undef TYPE_SAFE
}
#endif //CSV2XLS_CSV2XLS_TYPES_H
