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


/* Data definitions */
struct token {
    const char *value;
    size_t size;
};

struct row {
    struct token *cols;
    size_t size;
};
/* End of Data definitions */


/* Internal private functions */
/* End of Internal private functions */


/* Public function */
enum dsverr dsv_printrow(const char *line, size_t line_size, const char *w_str, const char *delimiters, bool wrap) {
    // Get terminal width (platform independent)
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

    static size_t cols = 0;
    if (cols == 0) {

        if (cols == 0)
            return DSV_NO_COLS;
    }

    return DSV_NOERR;
}
