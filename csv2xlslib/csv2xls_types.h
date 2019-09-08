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

using OutputRowLimit = skilled_type::SkilledType<std::uint32_t, struct TypeTagOutputRowLimit,
                                                 skilled_type::Equality,
                                                 skilled_type::Relativity>;

using Row = skilled_type::SkilledType<std::uint32_t, struct TypeTagRow,
                                      ComparableWith<OutputRowLimit>::templ,
                                      skilled_type::Incrementability,
                                      skilled_type::Equality,
                                      skilled_type::Relativity>;

using OutputColumnLimit = skilled_type::SkilledType<std::uint32_t, struct TypeTagOutputColumnLimit>;

using Column = skilled_type::SkilledType<std::uint32_t, struct TypeTagColumn,
                                         ComparableWith<OutputColumnLimit>::templ,
                                         skilled_type::Incrementability,
                                         skilled_type::Equality,
                                         skilled_type::Relativity>;

using CellContent = std::string_view;
using FileNumber = skilled_type::SkilledType<int, struct TypeTagFileNumber,
                                             skilled_type::Incrementability,
                                             skilled_type::Equality>;

#undef TYPE_SAFE

class BufferTooSmall : public std::logic_error
{
  public:
    explicit BufferTooSmall(std::string const& what): logic_error(what) {}
};

}
#endif //CSV2XLS_CSV2XLS_TYPES_H
