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

void print_file_not_found(const char *filename) {
    fprintf(stderr, "%s: \033[0;31mfatal error:\033[0m file not found: '%s'\n", APP_NAME, filename);
}


bool ischrin(const char el, const char *array, size_t nel) {
    for (size_t i = 0; i < nel; i++) {
        if (el == array[i]) return true;
    }
    return false;
}
