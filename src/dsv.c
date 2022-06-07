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


/* Data structures */
enum alignment {
    LEFT, RIGHT, NUMERIC_JUSTIFIED
};

struct token {
    const char *value;
    size_t size;
};

struct col {
    struct token value;
    size_t width;
    enum alignment align;
};

struct row {
    struct col *cols;
    size_t size;
};
/* End of Data structures */


/* Private functions */
struct row tokenize(const char *str, size_t str_len, const char *delimiters, const char *qualifiers, bool greedy) {
    // That's enough for today TODO: Tomorrow: Implement tokenize()
    struct row r = { NULL, 0 };
    return r;
}
/* End of Private functions */


/* Public function */
enum dsverr dsv_printrow(
        const char *line, size_t line_size,
        const char *w_config, const char *delimiters, const char *qualifiers, bool wrap, bool greedy
) {
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
    struct row row;
    if (cols == 0) {
        row = tokenize(line, line_size, delimiters, qualifiers, greedy);
        if (cols == 0 && row.size != 0)
            cols = row.size;
        if (cols == 0 && row.size == 0 && row.cols == NULL)
            return DSV_NO_COLS;
        if (cols != 0 && cols != row.size)
            return DSV_MALFORMED_ROW;
    }

    return DSV_NOERR;
}
