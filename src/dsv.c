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
#include "../include/glob.h"


/* Uitilites */
enum dsverr {
    EMPTY_1ST_ROW,
    EMPTY_ROW,
    MALFORMED,
};

void print_err(enum dsverr errcode) {
    switch (errcode) {
        case EMPTY_1ST_ROW:
            fprintf(stderr, "%s: \033[1;31merror:\033[0m cannot determine number of columns.\n", APP_NAME);
            break;
        case EMPTY_ROW:
            fprintf(stderr, "%s: \033[1;31merror:\033[0m row contains no data.\n", APP_NAME);
            break;
        case MALFORMED:
            fprintf(stderr, "%s: \033[1;31merror:\033[0m malformed row.\n", APP_NAME);
            break;
        default:
            fprintf(
                    stderr,
                    "%s: \033[1;31mDSV processor error:\033[0m Unrecognized error code '%d'",
                    APP_NAME, errcode
            );
            exit(EXIT_FAILURE);
    }
}
/* End of Uitilites */


/* Data definitions */
/* End of Data definitions */


/* Internal private functions */
/* End of Internal private functions */


/* Public function */
void dsv_printrow(const char *line, size_t line_size, const char *w_str, const char *delimiters, bool wrap) {
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

        if (cols == 0) {
            print_err(EMPTY_ROW);
            print_err(EMPTY_1ST_ROW);
            exit(EXIT_FAILURE);
        }
    }
}
