//
// Created by miketvo on 6/1/2022.
//
#include <stdlib.h>
#include <wchar.h>
#include <errno.h>
#include "../include/getline.h"


ssize_t getline(wchar_t **restrict lineptr, size_t *restrict n, FILE *restrict stream) {
    if (lineptr == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (ferror(stream)) {
        return -1;
    }

    if (feof(stream)) {
        return -1;
    }

    wchar_t *buffer = calloc(*n + 1, sizeof(wchar_t));
    wchar_t c;
    size_t len = 0;
    while (1) {
        c = fgetwc(stream);
        if (c == WEOF) break;
        buffer[len] = c;
        len++;
        if (len > *n) {
            wchar_t *temp_buffer;
            temp_buffer = realloc(buffer, (len + 1) * sizeof(wchar_t));
            if (temp_buffer == NULL) {
                free(buffer);
                errno = ENOMEM;
                return -1;
            }
            buffer = temp_buffer;
            *n = len;
        }
        if (c == '\n') break;
    }
    buffer[len] = '\0';

    *lineptr = buffer;
    return ((ssize_t) len);
}
