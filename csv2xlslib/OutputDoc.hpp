//
// Created by marcel on 12/20/17.
//

#ifndef CSV2XLS_OUTPUTDOC_H
#define CSV2XLS_OUTPUTDOC_H

#include "csv2xls_compound_types.h"
#include "csv2xls_types.h"
#include <memory>
#include <string>
namespace csv2xls
{
using HeadLineType = std::vector<std::string>;

class OutputDoc
{
  public:
    template <typename T>
    explicit OutputDoc(T&& x, HeadLineType const& head_line)
        : self_(new doc_type<T>(std::forward<T>(x)))
        ,output_column_limit(self_->columnLimit())
        ,m_headline(head_line)
    {
    }

    Row RowAfterClearSheet(XlsSheetName const& sheet_name);

    int writeInto(OutputFileName const& out_put_file);

    Column appendCell(CellContent cell_content);
    Row newLine();
  private:
    bool isEmpty();
    class concept_t
    {
      public:
        virtual ~concept_t() = default;

        virtual void clearSheet(XlsSheetName const& sheet_name)                = 0;
        virtual int  writeInto(OutputFileName const& out_put_file)             = 0;
        virtual void setCell(Row row, Column column, CellContent cell_content) = 0;
        virtual auto columnLimit()-> std::optional<OutputColumnLimit>          = 0;
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

        int writeInto(OutputFileName const& output_file_name) override
        {
            return x.writeInto(output_file_name);
        }

        void setCell(Row row, Column column, CellContent cell_content) override
        {
            x.setCell(row, column, cell_content);
        }

        auto columnLimit()-> std::optional<OutputColumnLimit> override
        {
            return x.columnLimit();
        }
      private:
        T x;
    };

  private:
    std::unique_ptr<concept_t> self_;
    Row m_row = Row(0);
    Column m_column = Column(0);
    std::optional<OutputColumnLimit> output_column_limit;
    HeadLineType   m_headline;

};
}

#endif //CSV2XLS_OUTPUTDOC_H