//
// Created by miketvo on 6/1/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/getline.h"


int full_test() {
    // Create test data and write into file on disk
    const char *TEST_DATA = "This is the test data.\nIt consists of 2 lines - this one and the one before it.";
    FILE *tempf = fopen("getline.test.data.temp.txt", "w+");
    if (tempf == NULL) {
        fprintf(stderr, "getline.test: %s.\n", strerror(errno));
        return 1;
    }
    fprintf(tempf, "%s", TEST_DATA);
    fclose(tempf);

    // Read test data from file just created on disk
    char *all_lines = calloc(1, sizeof(char));
    size_t total_len = 0;
    char *line = NULL;
    size_t buffer_len = 0;
    ssize_t line_len;
    tempf = fopen("getline.test.data.temp.txt", "r");
    while ((line_len = getline(&line, &buffer_len, tempf)) != -1) {
        total_len += line_len;
        all_lines = realloc(all_lines, total_len * sizeof(char));
        strncat(all_lines, line, line_len);
    }
    free(line);
    fclose(tempf);
    remove("getline.test.data.temp.txt");  // Remove temporary test file on disk

    if (strcmp(all_lines, TEST_DATA) != 0) {
        fprintf(stderr, "Assertion failed: Expected equality between:\nchar *all_lines'''\n%s\n'''\nand\nconst char *TEST_DATA'''\n%s\n'''\n", all_lines, TEST_DATA);
        free(all_lines);
        return 1;
    }

    free(all_lines);
    return 0;
}


int main() {
    if (full_test()) return 1;

    return 0;
}
