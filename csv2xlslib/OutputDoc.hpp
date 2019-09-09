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

class OutputDoc
{
  public:
    template <typename T>
    explicit OutputDoc(T && x)
        : self_(new doc_type<T>(std::forward<T>(x)))
        ,output_column_limit(self_->columnLimit())
    {
    }
    OutputDoc(OutputDoc && x)=default;
    OutputDoc& operator=(OutputDoc && other)=default;
    int writeInto(OutputFileName const& out_put_file, FileNumber file_number)const;
    void set(InputHasHeadLine input_has_head_line);
    Column appendCell(CellContent cell_content);
    Row newLine();
    bool isEmpty()const;
  private:
    class concept_t
    {
      public:
        virtual ~concept_t() = default;

        virtual int  writeInto(OutputFileName const& out_put_file, FileNumber file_number) const = 0;
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

        int writeInto(OutputFileName const& output_file_name, FileNumber file_number) const override
        {
            return x.writeInto(output_file_name, file_number);
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
    InputHasHeadLine m_input_has_head_line = InputHasHeadLine{false};
};
}

#endif //CSV2XLS_OUTPUTDOC_H
