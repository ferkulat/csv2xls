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

int OutPutDoc::write_to_file(const std::filesystem::path& file_name)
{
    return self_->write_to_file(file_name);
}

void OutPutDoc::setCell(Row row, Column col, const std::string& strlabel)
{
    self_->setCell(row, col, strlabel);
}
}