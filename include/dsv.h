//
// Created by miketvo on 6/1/2022.
//

#ifndef DSVCOL_DSV_H
#define DSVCOL_DSV_H

#include <stdlib.h>
#include <stdbool.h>


/***
 * Return type facility for dsv_printrow() below
 */
enum dsverr {
    DSV_NOERR,
    DSV_NO_COLS,
    DSV_EMPTY_ROW,
    DSV_MALFORMED_ROW,
};

/***
 * dsv.c top-level abstraction driver function. Takes in raw delimiter-separated line (const char *) and program
 * settings then spits out pretty-printed row on stdout.
 *
 * The number of columns is determined only during the first call (and stored in a static variable). All subsequence
 * calls force-print the data into that number of column regardless of actual number of tokens extracted. Thus, this
 * function expects the inputs to have equal amounts of tokens; if not, stop program execution and throw an error.
 *
 * The only exposed component of dsv.c (along with enum dsverr) to the end-user.
 *
 * @param line
 * @param line_size Not including the '\0' terminating character
 * @param w_config
 * @param delimiters
 * @param wrap
 */
enum dsverr dsv_printrow(
        const char *line, size_t line_size,  // Raw text
        const char *w_config, const char *delimiters, const char *qualifiers, bool wrap  // Program settings
);

#endif //DSVCOL_DSV_H
