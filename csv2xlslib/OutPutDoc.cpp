//
// Created by marcel on 12/20/17.
//

#include "OutPutDoc.hpp"
namespace csv2xls
{
void OutPutDoc::clearSheet(XlsSheetName const& sheet_name)
{
    self_->clearSheet(sheet_name);
}

int OutPutDoc::writeInto(OutPutFileName const& out_put_file)
{
    return self_->writeInto(out_put_file);
}

void OutPutDoc::setCell(Row row, Column col, CellContent const& cell_content)
{
    self_->setCell(row, col, cell_content);
}
}