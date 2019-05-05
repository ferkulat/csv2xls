//
// Created by marcel on 4/25/19.
//

#ifndef CSV2XLS_CSV2XLS_TYPES_H
#define CSV2XLS_CSV2XLS_TYPES_H

#include "TypeSafeSkillSet.h"
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
TYPE_SAFE(OutPutFileNameDigitCount, std::uint8_t)
TYPE_SAFE(OutPutFile, std::filesystem::path)
TYPE_SAFE(InputFile, std::filesystem::path)

using OutPutRowLimit = type_safe_skill_set::TypeSafeSkillSet<std::uint32_t, struct TypeTagOutPutRowLimit,
                                                             type_safe_skill_set::Equality,
                                                             type_safe_skill_set::RelativeComparable>;

using Row = type_safe_skill_set::TypeSafeSkillSet<std::uint32_t, struct TypeTagRow,
                                                  type_safe_skill_set::ComparableWith<OutPutRowLimit>::templ,
                                                  type_safe_skill_set::PreIncrementable,
                                                  type_safe_skill_set::Equality>;

using OutPutColumnLimit = type_safe_skill_set::TypeSafeSkillSet<std::uint32_t, struct TypeTagOutPutColumnLimit>;

using Column = type_safe_skill_set::TypeSafeSkillSet<std::uint32_t, struct TypeTagColumn,
                                                     type_safe_skill_set::ComparableWith<OutPutColumnLimit>::templ,
                                                     type_safe_skill_set::PreIncrementable,
                                                     type_safe_skill_set::Equality>;


#undef TYPE_SAFE
}
#endif //CSV2XLS_CSV2XLS_TYPES_H
