#include "readHeadLine.hpp"
#include <errno.h>
#include <iostream>
#include "callback.hpp"
namespace csv2xls
{
void readHeadLine(	std::fstream &csv_input,
					csv_file_t &csv_in,
					xls_file_t &xls_out)
{
	std::string head_line_buffer;
	if (!getline(csv_input, head_line_buffer).fail())
	{
		//getline omits newline from input stream
		// but csv_parser needs it
		head_line_buffer.append("\n");

		if (csv_parse(&csv_in.csv_file_parser, head_line_buffer.c_str(),
				head_line_buffer.size(),
				/* register call back function for end of csv field*/
				csv_cb_headline_field,
				/* register call back function for end of csv row*/
				csv_cb_end_of_row,
				/* to be passed to the call back functions*/
				&xls_out) != head_line_buffer.size())
		{
			std::cerr << "Error while parsing file: %s" << "\n"
					<< csv_strerror(csv_error(&csv_in.csv_file_parser)) << "\n";
			exit(EXIT_FAILURE);
		}
	}

}
}
