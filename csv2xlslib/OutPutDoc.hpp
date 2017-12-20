//
// Created by marcel on 12/20/17.
//

#ifndef CSV2XLS_OUTPUTDOC_H
#define CSV2XLS_OUTPUTDOC_H

#include <string>
#include <memory>

class OutPutDoc {
public:
    template<typename T>
    OutPutDoc(T&& x) : self_(new doc_type<T>(std::move(x))){}

    void clear_sheet(const std::string& sheetname);

    int write_to_file(const std::string &file_name);

    void label( unsigned int row,
                unsigned int col,
                const std::string& strlabel);
private:

    class concept_t
    {
    public:
        virtual ~concept_t() = default;

        virtual void clear_sheet(const std::string& sheetname)= 0;
        virtual int write_to_file(const std::string &file_name) = 0;
        virtual void label( unsigned int row,
                            unsigned int col,
                            const std::string& strlabel) = 0;
    };
    template <typename T>
    class doc_type : public concept_t
    {
    public:
        doc_type(T x):x(std::move(x)){}

        void clear_sheet(const std::string &sheetname) override {
            x.clear_sheet(sheetname);
        }

        int write_to_file(const std::string &file_name) override {
            return x.write_to_file(file_name);
        }

        void label(unsigned int row,
                   unsigned int col,
                   const std::string &strlabel) override {
            x.label(row, col, strlabel);
        }

    private:
        T x;
    };
private:
    std::unique_ptr<concept_t> self_;
};


#endif //CSV2XLS_OUTPUTDOC_H
