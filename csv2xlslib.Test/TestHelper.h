//
// Created by marcel on 6/2/19.
//

#ifndef CSV2XLS_TESTHELPER_H
#define CSV2XLS_TESTHELPER_H
#include <csv2xls_compound_types.h>
#include <csv2xls_types.h>
#include <memory>
#include <optional>
#include "default_values.h"
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
    int writeInto(OutputFileName const& /*file_name*/, FileNumber /*file_number*/)
    {
        called_write_to_file++;
        files.push_back(std::move(cells));
        cells.clear();
        return 0;
    }
    void setCell(Row row, Column col, CellContent strlabel)
    {
        while (cells.size() < row.Get()+1)
            cells.emplace_back(std::vector<std::string>());
        while (cells[row.Get()].size() < col.Get())
            cells[row.Get()].emplace_back("");

        called_label++;
        cells[row.Get()].emplace_back(strlabel);
    }
    auto columnLimit() -> std::optional<OutputColumnLimit>
    {
        return out_put_column_limit;
    }

    int               called_clear_sheet   = 0;
    int               called_write_to_file = 0;
    int               called_label         = 0;
    std::vector<std::vector<std::string>> cells;
    std::vector<std::vector<std::vector<std::string>>> files;
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
    int writeInto(OutputFileName const& file_name, FileNumber file_number) const
    {
        return wrapped->writeInto(file_name, file_number);
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
