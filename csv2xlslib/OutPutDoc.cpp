//
// Created by marcel on 12/20/17.
//

#include "OutPutDoc.hpp"

void OutPutDoc::clear_sheet(const std::string& sheetname)
{
    self_->clear_sheet(sheetname);
}

int OutPutDoc::write_to_file(const std::string &file_name)
{
    return self_->write_to_file(file_name);
}

void OutPutDoc::label(unsigned int row,
                      unsigned int col,
                      const std::string& strlabel)
{
    self_->label(row, col, strlabel);
}
