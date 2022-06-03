//
// Created by miketvo on 6/1/2022.
//
#if defined(_WIN32)
#define PLATFORM_DECTECTED 1
#include <windows.h>
#else
#define PLATFORM_DECTECTED 1
#include <sys/ioctl.h>
#endif
#ifndef PLATFORM_DECTECTED
#error Could not detect operating system platform
#endif
#include <stdio.h>
#include <stdbool.h>
#include "../include/dsv.h"


// TODO: Implement this
size_t dsv_colcount(const char *source, size_t source_size, const char *delimiters) {
    return 6;  // 6 according to /test/data/bos2021ModC.csv TODO: Remove this magic number
}

// TODO: Implement this
void dsv_printline(
        const char *source, size_t source_size, size_t cols,
        const char *w_str, const char *delimiters, bool wrap
) {
    size_t term_w;
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    term_w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
    term_w = max.ws_col;
#endif

    size_t col_w = term_w / cols;
    for (size_t i = 0; i < source_size && i < term_w; i++) {
        putchar(source[i]);
        if (source[i] == '\n') return;
    }
    putchar('\n');
}
