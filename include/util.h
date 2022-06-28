//
// Created by miketvo on 5/23/2022.
//

#ifndef DSVCOL_UTIL_H
#define DSVCOL_UTIL_H

#include <stdbool.h>
#include "../include/dsv.h"

void print_help();
void print_version();
void print_bad_usage();
void print_optarg_error(const wchar_t *optarg);
void print_text_qualifer_optarg_error(const wchar_t *tq_optarg);
void print_text_qualifer_collision(wchar_t tq);
void print_file_not_found(const char *filename, const char *message);
void print_dsverr(enum dsverr errcode, size_t rowno);


bool ischrin(char el, const char *array, size_t nel);
bool wcischrin(wchar_t el, const wchar_t *array, size_t nel);

#endif //DSVCOL_UTIL_H
