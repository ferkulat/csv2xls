//
// Created by marcel on 9/8/19.
//

#ifndef CSV2XLS_PARSECSVSTREAM_HPP
#define CSV2XLS_PARSECSVSTREAM_HPP
#include "OutputDoc.hpp"
namespace csv2xls
{
int parseCsvStream(Config const& config, std::istream& csv_input, std::function<OutputDoc()> makeOutputDoc);
}
#endif // CSV2XLS_PARSECSVSTREAM_HPP
