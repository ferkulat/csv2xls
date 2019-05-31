//
// Created by marcel on 5/31/19.
//
#include "MatchVariantType.h"
#include "XlsFile.hpp"
#include "csv2xls_compound_types.h"
#include "readBuffer.h"
#include <Skills.h>
#include <fstream>
namespace csv2xls
{
auto writeCell(xls_file_t& output_doc, CellContent const& cell)
{
    output_doc.output_doc.appendCell( cell);
}

auto WriteRowInto(xls_file_t& output_doc)
{
    return [&output_doc](CsvType csv_type) {
        MatchType(csv_type,
            [&](CellContent const& cell) {writeCell(output_doc, cell);},
            [](auto const& ) {}
        );
        return csv_type;
    };
}

auto convertCsv(xls_file_t, Buffer& buffer, std::fstream& )
{
    return read(buffer, CsvSeparator(';'));
}
}