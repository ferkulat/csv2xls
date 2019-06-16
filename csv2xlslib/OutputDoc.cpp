//
// Created by marcel on 12/20/17.
//

#include "OutputDoc.hpp"
namespace csv2xls
{
Row OutputDoc::RowAfterClearSheet()
{
    self_->clearSheet();
    m_column = Column(0);
    m_row    = Row(0);
    if (m_headline.size())
    {
        for(auto const& column : m_headline )
            appendCell(CellContent(column.c_str(), column.size()));
        newLine();
    }
    return m_row;
}

int OutputDoc::writeInto(OutputFileName const& out_put_file) const
{
    if(isEmpty())
        return 0;
    return self_->writeInto(out_put_file, m_file_number);
}
void OutputDoc::setHeadLine(HeadLineType const& head_line)
{
    m_headline = head_line;
}

bool OutputDoc::isEmpty()const
{
    return (m_headline.size())
            ? (m_row == Row(1))&&(m_column == Column(0))
            : (m_row == Row(0))&&(m_column == Column(0));
}

Column OutputDoc::appendCell(CellContent cell_content)
{
    if (output_column_limit && m_column.isGreaterEqual (output_column_limit.value()))
    {
        return m_column;
    }
    self_->setCell(m_row, m_column, cell_content);
    ++m_column;
    return m_column;
}
Row OutputDoc::newLine()
{
    ++m_row;
    m_column = Column(0);
    return m_row;
}
}