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
#include <stdio.h>
#include <stdbool.h>
#ifndef PLATFORM_DECTECTED
#include "../include/util.h"
#endif
#include "../include/dsv.h"


// TODO: Implement this
void dsv_printline(const char *source, size_t source_size, const char *w_str, const char *delimiters, bool wrap) {
    size_t term_w;
#ifndef PLATFORM_DECTECTED
    print_platform_undefined();
    exit(EXIT_FAILURE);
#elif defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    term_w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
    term_w = max.ws_col;
#endif

    printf("%u-", (unsigned int) term_w);
}
