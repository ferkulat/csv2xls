#include "callback.hpp"
#include "XlsFile.hpp"
#include "csv.hpp"
namespace csv2xls
{
void
csv_cb_end_of_field (void *s,
                     size_t len,
                     void *data)
{
    char       *csv_field = (char*)s;
    xls_file_t *xls_file  = (xls_file_t*)data;

    #if  CSV_MAJOR < 3
    *(csv_field+len) ='\0'; /*terminate string*/
    #endif

    xls_append_cell(xls_file,csv_field);
}/* ----- end of function csv_cb_end_of_field ----- */


void
csv_cb_headline_field(void *s,
                      size_t len,
                      void *data)
{
    char       *csv_field = (char*)s;
    xls_file_t *xls_file  = (xls_file_t*)data;
    if (XLS_MAX_COLUMNS >= xls_file->headline.size())
    {
        #if  CSV_MAJOR < 3
        *(csv_field+len) ='\0'; /*terminate string*/
        #endif
        xls_append_cell(xls_file, csv_field);
        xls_file->headline.push_back(csv_field);
    }
}/* ----- end of function csv_cb_headline_field ----- */

void
csv_cb_end_of_row (int c,
                   void *data)
{
    xls_file_t *xls_file = (xls_file_t*)data;
    xls_newline(xls_file);
}/* ----- end of function csv_cb_end_of_row ----- */
}/* ---- end of namespace csv2xls ---- */
