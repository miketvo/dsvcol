//
// Created by miketvo on 5/23/2022.
//
#include <stdio.h>
#include "../include/glob.h"
#include "../include/util.h"


void print_help() {
    printf("Usage: %s [options] [file...]\n", APP_NAME);
}

void print_version() {
    printf("%s version %s\n", APP_NAME, APP_VERSION);
}

void print_bad_usage() {
    fprintf(stderr, "%s: bad usage\nTry '%s -h' or '%s --help' for more information.\n", APP_NAME, APP_NAME, APP_NAME);
}

void print_optarg_error(const char *optarg) {
    fprintf(stderr, "%s: unknown argument '%s'\n", APP_NAME, optarg);
}

void print_file_not_found(const char *filename, const char *message) {
    fprintf(stderr, "%s: \033[1;31m%s:\033[0m '%s'\n", APP_NAME, message, filename);
}

void print_dsverr(enum dsverr errcode, size_t rowno) {
    switch (errcode) {
        case DSV_NO_COLS:
            fprintf(stderr, "%s: \033[1;31merror:\033[0m row %llu contains no data.\n", APP_NAME, (unsigned long long) rowno);
            fprintf(stderr, "%s: \033[1;31merror:\033[0m cannot determine number of columns.\n", APP_NAME);
            break;
        case DSV_EMPTY_ROW:
            fprintf(stderr, "%s: \033[1;31merror:\033[0m row %llu contains no data.\n", APP_NAME, (unsigned long long) rowno);
            break;
        case DSV_MALFORMED_ROW:
            fprintf(stderr, "%s: \033[1;31merror:\033[0m malformed row: %llu.\n", APP_NAME, (unsigned long long) rowno);
            break;
        default:
            fprintf(
                    stderr,
                    "%s: \033[1;31mDSV processor error:\033[0m Unrecognized error code '%d'",
                    APP_NAME, (int) errcode
            );
            exit(EXIT_FAILURE);
    }
}


bool ischrin(const char el, const char *array, size_t nel) {
    for (size_t i = 0; i < nel; i++) {
        if (el == array[i]) return true;
    }
    return false;
}
