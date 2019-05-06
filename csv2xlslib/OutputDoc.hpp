//
// Created by marcel on 12/20/17.
//

#ifndef CSV2XLS_OUTPUTDOC_H
#define CSV2XLS_OUTPUTDOC_H

#include "csv2xls_types.h"
#include <filesystem>
#include <memory>
#include <string>
namespace csv2xls
{
class OutputDoc
{
  public:
    template <typename T>
    explicit OutputDoc(T&& x)
        : self_(new doc_type<T>(std::forward<T>(x)))
    {
    }

    void clearSheet(XlsSheetName const& sheet_name);

    int writeInto(OutputFileName const& out_put_file);

    void setCell(Row row, Column column, CellContent const& cell_content);

  private:
    class concept_t
    {
      public:
        virtual ~concept_t() = default;

        virtual void clearSheet(XlsSheetName const& sheet_name)                       = 0;
        virtual int  writeInto(OutputFileName const& out_put_file)                        = 0;
        virtual void setCell(Row row, Column column, CellContent const& cell_content) = 0;
    };
    template <typename T> class doc_type : public concept_t
    {
      public:
        doc_type(T x_)
            : x(std::move(x_))
        {
        }

        void clearSheet(XlsSheetName const& sheet_name) override
        {
            x.clearSheet(sheet_name);
        }

        int writeInto(OutputFileName const& out_put_file) override
        {
            return x.writeInto(out_put_file);
        }

        void setCell(Row row, Column column, CellContent const& cell_content) override
        {
            x.setCell(row, column, cell_content);
        }

      private:
        T x;
    };

  private:
    std::unique_ptr<concept_t> self_;
};
}

#endif //CSV2XLS_OUTPUTDOC_H
