//
// Created by marcel on 12/20/17.
//

#include "OutputDoc.hpp"
namespace csv2xls
{
void OutputDoc::clearSheet(XlsSheetName const& sheet_name)
{
    self_->clearSheet(sheet_name);
}

int OutputDoc::writeInto(OutputFileName const& out_put_file)
{
    return self_->writeInto(out_put_file);
}

void OutputDoc::setCell(Row row, Column col, CellContent const& cell_content)
{
    self_->setCell(row, col, cell_content);
}
}