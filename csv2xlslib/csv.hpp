/**
 * @file csv.hpp
 *
 * csv2xls - convert csv files into one or more Excel(TM) files
 * Copyright (C) 2012  Marcel Schneider
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU GENERAL PUBLIC LICENSE
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU GENERAL PUBLIC LICENSE for more details.
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 *
 * Free Software Foundation Inc.
 * 51 Franklin Street
 * Fifth Floor
 * Boston
 * MA  02110-1301  USA
 */

#ifndef  CSV_HPP
#define  CSV_HPP

#include <memory>
#include <iostream>
struct csv_parser;
namespace csv2xls
{
    struct ParserDeleter {
        void operator()(struct csv_parser *p);
    };

    struct Parser
    {
        explicit Parser(unsigned char tab_delimiter);
        std::unique_ptr<csv_parser, ParserDeleter> csv_file_parser; /** < the parser */
        unsigned char tab_delimiter;

    } ;

    /**
     * \brief hides some low lowlevel of libcsv
     *
     * @param parser
     */
    Parser
    createParser(unsigned char tab_delimiter);

} /* ----- end of namesace csv2xls ----- */
#endif   /* ----- #ifndef CSV_HPP  ----- */
