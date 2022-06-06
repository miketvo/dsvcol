//
// Created by miketvo on 5/26/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/delimiter_optarg.h"


int main() {
    struct testcase {
        const char *input;
        size_t size;
        const char *assertion;
    };

    const struct testcase TEST[] = {
            {"abc",      3, "abc"},
            {"abcc",     4, "abc"},
            {"abbc",     4, "abc"},
            {"aabb",     4, "ab"},
            {"aaab",     4, "ab"},
            {"aaaa",     4, "a"},
            {"a\\\\\\t", 5, "a\\\t"},
            {NULL,       0, NULL},  // This is to signal the end of the array. DO NOT REMOVE.
    };

    int return_val = 0;
    char *buffer;
    size_t i = 0;
    while (TEST[i].input != NULL) {  // Test for the end of the array
        buffer = calloc(TEST[i].size + 1, sizeof(char));
        delimiter_optarg_nparse(TEST[i].input, buffer, TEST[i].size);
        if (strncmp(buffer, TEST[i].assertion, TEST[i].size) != 0) {
            fprintf(
                    stderr,
                    "ERROR: [ index( %llu ), input( '%s' ), size( %llu ) ]: buffer( '%s' ) != assertion( '%s' )\n",
                    (unsigned long long) i, TEST[i].input, (unsigned long long) TEST[i].size, buffer, TEST[i].assertion
            );
            free(buffer);
            buffer = NULL;
            if (return_val != 1) return_val = 1;
        }
        free(buffer);
        buffer = NULL;
        i++;
    }

    return return_val;
}
