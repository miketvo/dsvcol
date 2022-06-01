//
// Created by miketvo on 6/1/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/io.h"


int main() {
    // Create test data and write into file on disk
    const char *TEST_DATA = "This is the test data.\nIt consists of 2 lines - this one and the one before it.";
    FILE *tempf = fopen("io.getline.test.data.temp.txt", "w+");
    if (tempf == NULL) {
        fprintf(stderr, "io.getline.test: failed to create test data file.\n");
        return 1;
    }
    fprintf(tempf, "%s", TEST_DATA);
    fclose(tempf);

    // Read test data from file just created on disk
    char *all_lines = calloc(1, sizeof(char));
    size_t total_len = 1;  // Including terminating null character '\0'
    char *line = NULL;
    size_t buffer_len = 0;
    ssize_t line_len;
    tempf = fopen("io.getline.test.data.temp.txt", "r");
    do {
        line_len = getline(&line, &buffer_len, tempf);
        total_len += line_len;
        all_lines = realloc(all_lines, total_len * sizeof(char));
    } while (line_len != -1);
    free(line);
    fclose(tempf);
    remove("io.getline.test.data.temp.txt");  // Remove temporary test file on disk

    return 0;
}
