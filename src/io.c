//
// Created by miketvo on 6/1/2022.
//
#include <stdlib.h>
#include <errno.h>
#include "../include/io.h"


ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream) {
    if (lineptr == NULL || n == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    if (ferror (stream)) {
        return -1;
    }

    if (feof(stream)) {
        return -1;
    }

    char *buffer = calloc(*n, sizeof(char));
    char c;
    size_t len = 0;
    while (1) {
        c = (char) fgetc(stream);
        buffer[len] = c;
        len++;
        if (len + 1 > *n) {
            buffer = realloc(buffer, len + 1 * sizeof(char));
            *n = len;
        }
        if (c == '\n' || c == EOF) break;
    };
    buffer[len + 1] = '\0';

    *lineptr = buffer;
    return((ssize_t) len);
}
