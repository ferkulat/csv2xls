//
// Created by marcel on 4/25/19.
//

#ifndef CSV2XLS_CSV2XLS_TYPES_H
#define CSV2XLS_CSV2XLS_TYPES_H

#include <checked_cmd.h>
#include <filesystem>

#define TYPE_SAFE(Name, Type) using Name = \
    CheckedCmd::CheckedCmdTypesafe::Typesafe<Type, struct TypeTag##Name>;

TYPE_SAFE(CsvSeparatorIsTab       , bool)
TYPE_SAFE(InputHasHeadLine        , bool)
TYPE_SAFE(PrintVersionInfo        , bool)
TYPE_SAFE(CsvSeparator            , char)
TYPE_SAFE(InputBufferSize         , std::streamsize)
TYPE_SAFE(XlsSheetName            , std::string)
TYPE_SAFE(OutPutFileNameDigitCount, std::uint8_t)
TYPE_SAFE(OutPutRowLimit          , std::uint32_t)
TYPE_SAFE(OutPutFile              , std::filesystem::path)
TYPE_SAFE(InputFile               , std::filesystem::path)


bool operator<(OutPutRowLimit v1, OutPutRowLimit v2);
bool operator<(OutPutFileNameDigitCount v1, OutPutFileNameDigitCount v2);

#undef TYPE_SAFE
#endif //CSV2XLS_CSV2XLS_TYPES_H
