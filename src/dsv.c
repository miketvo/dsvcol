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
#include <string.h>
#include <stdbool.h>
#include "../include/dsv.h"
#include "../include/util.h"


/* Private functions and data structures */
struct token {
    const char *begin;
    const char *end;
};

struct token tokenize(const char *str, size_t str_size, const char *delimiters, const char *qualifiers, bool greedy) {
    struct token result = {str, str};

    while (!ischrin(*result.end, delimiters, strlen(delimiters)) && *result.end != '\n' && result.end - str < str_size) {
        if (*result.end == qualifiers[0]) {
            result.end++;
            while (*result.end != qualifiers[1] && *result.end != '\n' && result.end - str < str_size)
                result.end++;
        }
        result.end++;
    }

    if (greedy) {
        while (ischrin(*result.end, delimiters, strlen(delimiters)))
            result.end++;
    } else result.end++;

    return result;
}


size_t count_cols(const char *line, size_t line_size, const char *delimiters, const char *qualifiers, bool greedy) {
    size_t count = 0;
    struct token current_token = {line, line };

    while (current_token.end - line < line_size) {
        current_token = tokenize(current_token.end, line_size - (current_token.end - line), delimiters, qualifiers, greedy);
        count++;
    }
    return count;
}


enum alignment {
    LEFT, RIGHT
};

void print_col(const char *token, size_t col_width, enum alignment col_align) {
    const size_t COL_WIDTH_DIGIT_LIMIT = 100;
    char col_width_str[COL_WIDTH_DIGIT_LIMIT];
    char *format_str;
    switch (col_align) {
        case RIGHT: {
            snprintf(col_width_str, COL_WIDTH_DIGIT_LIMIT, "%llu", (unsigned long long) col_width - 1);
            format_str = calloc(strlen(col_width_str) * 2 + 5, sizeof(char));
            strcat(format_str, "%");
            strcat(format_str, col_width_str);
            strcat(format_str, ".");
            strcat(format_str, col_width_str);
            strcat(format_str, "s ");
            break;
        }
        case LEFT:
        default: {
            snprintf(col_width_str, COL_WIDTH_DIGIT_LIMIT, "%llu", col_width - 1);
            format_str = calloc(strlen(col_width_str) * 2 + 6, sizeof(char));
            strcat(format_str, "%-");
            strcat(format_str, col_width_str);
            strcat(format_str, ".");
            strcat(format_str, col_width_str);
            strcat(format_str, "s ");
            break;
        }
    }
    printf(format_str, token);
    free(format_str);
}
/* End of Private functions and data structures */


/* Public function */
enum dsverr dsv_printrow(
        const char *line, size_t line_size,
        const char *w_config, const char *delimiters, const char *qualifiers, bool wrap, bool greedy
) {
    // Get terminal width (platform independent)
    static size_t term_w = 0;
    if (term_w == 0) {
#if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        term_w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
        struct winsize max;
        ioctl(0, TIOCGWINSZ , &max);
        term_w = max.ws_col;
#endif
    }

    static size_t cols = 0;
    if (cols == 0) {
        cols = count_cols(line, line_size, delimiters, qualifiers, greedy);
        if (cols == 0)
            return DSV_NO_COLS;
    }

    size_t curr_cols = 0;
    struct token current_token = { line, line };
    char *current_token_str;

    while (current_token.end - line < line_size) {
        if (curr_cols > cols) {
            putchar('\n');
            return DSV_MALFORMED_ROW;
        }

        current_token = tokenize(current_token.end, line_size - (current_token.end - line), delimiters, qualifiers, greedy);
        current_token_str = calloc(current_token.end - current_token.begin + 2, sizeof(char));
        strncpy(current_token_str, current_token.begin, current_token.end - current_token.begin - 1);
        print_col(current_token_str, term_w / cols, LEFT);
        free(current_token_str);

        curr_cols++;
    }
    putchar('\n');

    if (0 < curr_cols && curr_cols < cols) return DSV_MALFORMED_ROW;  // Ignore blank lines
    return DSV_NOERR;
}
