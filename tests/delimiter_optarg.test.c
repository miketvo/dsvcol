//
// Created by miketvo on 5/26/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/delimiter_optarg.h"


int main() {
    const char *TEST_CASES[] = {
            "abc",
            "abcc",
            "abbc",
            "aabb",
            "aaab",
            "aaaa",
            ""  // This signals the end of the array. DO NOT REMOVE.
    };

    const size_t TEST_SIZES[] = {  // Not including terminating character '\0'
            3,
            4,
            4,
            4,
            4,
            4,
            0  // This signals the end of the array. DO NOT REMOVE.
    };

    const char *TEST_ASSERTS[] = {
            "abc",
            "abc",
            "ab",
            "ab",
            "a",
            ""  // This signals the end of the array. DO NOT REMOVE.
    };

    char *buffer;
    size_t i = 0;
    while (strcmp(TEST_CASES[i], "") != 0) {  // Test for the end of the array
        buffer = calloc(TEST_SIZES[i] + 1, sizeof(char));
        delimiter_optarg_nparse(TEST_CASES[i], buffer, TEST_SIZES[i] + 1);
        if (strncmp(buffer, TEST_ASSERTS[i], TEST_SIZES[i]) != 0) {
            fprintf(stderr, "ERROR: index: %d - buffer(%s) != assertion(%s)\n", i, buffer, TEST_ASSERTS[i]);
            free(buffer);
            return 1;
        }
        free(buffer);
        i++;
    }

    return 0;
}
