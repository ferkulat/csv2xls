//
// Created by marcel on 6/2/19.
//

#ifndef CSV2XLS_TESTHELPER_H
#define CSV2XLS_TESTHELPER_H
#include <XlsFile.hpp>
#include <csv2xls_compound_types.h>
#include <csv2xls_types.h>
#include <memory>
#include <optional>
namespace csv2xls::Testing
{

class DummyWorkBook
{
  public:
    void clearSheet()
    {
        called_clear_sheet++;
        cells.clear();
    }
    int writeInto(OutputFileName const& /*file_name*/)
    {
        called_write_to_file++;
        return 0;
    }
    void setCell(Row /*row*/, Column /*col*/, CellContent strlabel)
    {
        called_label++;
        cells.emplace_back(strlabel.start, strlabel.length);
    }
    auto columnLimit() -> std::optional<OutputColumnLimit>
    {
        return out_put_column_limit;
    }

    int               called_clear_sheet   = 0;
    int               called_write_to_file = 0;
    int               called_label         = 0;
    std::vector<std::string> cells;
    OutputColumnLimit out_put_column_limit = csv2xls::XLS_MAX_COLUMNS;
};
template <typename T> class WrapperWorkBook
{
    std::shared_ptr<T> wrapped;

  public:
    WrapperWorkBook(std::shared_ptr<T> wrapped_)
        : wrapped(wrapped_)
    {
    }

    void clearSheet()
    {
        wrapped->clearSheet();
    }
    int writeInto(OutputFileName const& file_name)
    {
        return wrapped->writeInto(file_name);
    }
    void setCell(Row row, Column column, CellContent cell_content)
    {
        wrapped->setCell(row, column, cell_content);
    }
    auto columnLimit() -> std::optional<OutputColumnLimit>
    {
        return wrapped->columnLimit();
    }
};
}
#endif //CSV2XLS_TESTHELPER_H
