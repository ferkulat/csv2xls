/* *
 *
 * @file csv2xls.cpp:
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

#include <iostream>
#include <conversion.h>
#include "parsecmd.hpp"
#include "parseCsvFile.hpp"

int main(int argc, char *argv[])
{

    unsigned int d=12;
    if (d < 12){
        std::cout << "lol";
    }
    try
    {
        return csv2xls::parseCsvFile(csv2xls::parse_commandline(argc, argv));
    }
    catch(csv2xls::BadCommandLineOption const& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch(csv2xls::FileNotOpen const& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch (BadNumericConversion const& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch(csv2xls::BufferTooSmall const& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
}/* ----- end of function main ----- */
