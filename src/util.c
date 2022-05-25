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
