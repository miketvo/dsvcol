//
// Created by miketvo on 5/23/2022.
//

#ifndef DSVCOL_UTIL_H
#define DSVCOL_UTIL_H

#include <stdbool.h>

void print_help();
void print_version();
void print_bad_usage();
void print_optarg_error(const char *optarg);


bool ischrin(char el, const char *array, size_t nel);

#endif //DSVCOL_UTIL_H
