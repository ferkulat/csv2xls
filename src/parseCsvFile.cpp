#include "parseCsvFile.hpp"
#include "memory.hpp"
#include "callback.hpp"

namespace csv2xls
{
//    using namespace std;
void
parseCsvFile(fstream &csv_input, csv_file_t &csv_in, xls_file_t &xls_out, cmd_opts_t &options )
{
    char_buf_t input_buffer;
    input_buffer.size = options.input_buffer_size;

    if ( !get_buffer(input_buffer))
    {
        cerr << "could not allocate " << options.input_buffer_size
             << " bytes of memory" << endl;
        exit(EXIT_FAILURE);
    }
    cerr << "allocated " << input_buffer.size << " bytes for input buffer" << endl;

/**
 * read csv input lines and put it into xls file
 */
    unsigned long bytes_read;

    while(csv_input.good())
    {
        csv_input.read(input_buffer.mem, input_buffer.size);
        bytes_read = csv_input.gcount();

        if (csv_parse(&csv_in.csv_file_parser,
                      input_buffer.mem,
                      bytes_read,
                      /* register call back function for end of csv field*/
                      csv_cb_end_of_field,
                      /* register call back function for end of csv row*/
                      csv_cb_end_of_row,
                      /* to be passed to the call back functions*/
                      &xls_out
                     ) != bytes_read)
        {
            cerr << "Error while parsing file: %s" << endl
                 << csv_strerror(csv_error(&csv_in.csv_file_parser)) << endl;
        }

    }
    free(input_buffer.mem);

}
}