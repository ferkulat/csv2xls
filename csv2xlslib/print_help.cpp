/*
 * print_help.cpp
 *
 *  Created on: 17.02.2014
 *      Author: eagle
 */
#ifdef __MINGW32__
#include <_mingw.h>
#include <crtdefs.h>
#endif

#include "print_help.h"
#include "default_values.h"
#include <iostream>

namespace csv2xls

{
void print_help(char*executable)
{
    std::cout << "Usage: " << executable << " [options] file" << std::endl
            << std::endl
            << "Description: Read csv file and convert it to one or more excel files."
            << std::endl << std::endl;

    std::cout << "options:" << std::endl << std::endl;

    std::cout << "-b num" << "\tset buffer size for parsing csv to num bytes."
            << std::endl << "\tDefaults to " << DEFAULT_CSV_BUFFER_SIZE << "."
            << std::endl << "\tMaximum value: " << MAX_CSV_BUFFER_SIZE << "."
            << std::endl << std::endl;

    std::cout << "-d c" << "\tset csv tab delimiter to c. Default: \'"
            << (char) DEFAULT_CSV_TAB_DELIMITER << "\'" << std::endl
            << std::endl;

    std::cout << "-t" << "\tset csv tab delimiter to tab character (ASCII 9)."
            << std::endl;

    std::cout << "-h" << "\tPrint this help text and exit." << std::endl
            << std::endl;

    std::cout << "-H" << "\tTake first line from csv file as head line for each"
            << std::endl << "\tproduced excel file. " << std::endl << std::endl;

    std::cout << "-l num" << "\tbreak xls output into files with max num lines"
            << std::endl << "\tDefaults to " << DEFAULT_XLS_MAX_LINES << "."
            << std::endl << "\tMaximum value: " << DEFAULT_XLS_MAX_LINES << "."
            << "\tMinimum value: " << 2 << "." << std::endl << std::endl;

    std::cout << "-o name"
            << "\tSet output file name to \'name\'. If this option is"
            << " not set," << std::endl
            << "\ttake csv input file name and replace \'.csv\' with "
            << "\'.xls\'." << std::endl
            << "\tIf \'name\' does not end with \'.xls\', it will be "
            << "added by program." << std::endl << std::endl;

    std::cout << "-w name" << "\tSet the excel worksheet name to \'name\'. "
            << "Defaults to \'Table 1\'" << std::endl << std::endl;

    std::cout << "-D num"
            << "\tSet excel file name numbering to \'num\' digits "
            << "with leading zeros." << std::endl << "\tDefault: "
            << DEFAULT_XLS_DIGIT_COUNT << "." << " Maximum value: "
            << MAX_XLS_DIGIT_COUNT << "." << std::endl << std::endl;
    std::cout << "-v" << "\tPrint version and exit" << std::endl;

}
}

