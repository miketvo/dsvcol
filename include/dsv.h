//
// Created by miketvo on 6/1/2022.
//

#ifndef DSVCOL_DSV_H
#define DSVCOL_DSV_H

#include <stdlib.h>
#include <stdbool.h>


size_t dsv_colcount(const char *source, size_t source_size, const char *delimiters);

void dsv_printline(
        const char *source, size_t source_size, size_t cols,
        const char *w_str, const char *delimiters, bool wrap
);

#endif //DSVCOL_DSV_H
