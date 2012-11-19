#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <stddef.h>

namespace csv2xls
{
/**
 * \fn void csv_cb_end_of_field (void *s, size_t len, void *data)
 * \brief Call back function if csv parser reaches end of a field
 *
 * The csv parser sets the parameters.
 * @param s
 * Pointer to the string the parser read in the current field
 * @param len
 * Length of string `s`
 * @param data
 * A pointer to the data structure we registered during `csv_parse()`.
 */
void
csv_cb_end_of_field (void *s,
                     size_t len,
                     void *data);

/**
 * \fn void csv_cb_end_of_row (int c, void *data)
 *
 * \brief Call back function if csv parser reaches end of a row.
 *
 * The csv parser sets the parameters.
 * @param c
 * @param data
 * A pointer to the data structure we registered during `csv_parse()`.
 */
void
csv_cb_end_of_row (int c,
                   void *data);

/**
 * \fn void csv_cb_headline_field(void *s, size_t len, void *data)
 *
 * \brief Call back function if csv parser reaches end of a field in the head line
 *
 * The head line needs special handling. Additionaly to writng the field into
 * the xls file, we store it to reuse it later without parsing again.
 * The csv parser sets the parameters.
 * @param s
 * Pointer to the string the parser read in the current field
 * @param len
 * Length of string `s`
 * @param data
 * A pointer to a data structure we registered during `csv_parse()`.
 */
void
csv_cb_headline_field(void *s,
                      size_t len,
                      void *data);
}/* ---- end of namespace csv2xls ---- */

#endif
