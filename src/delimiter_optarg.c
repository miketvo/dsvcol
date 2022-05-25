//
// Created by miketvo on 5/24/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "../include/glob.h"
#include "../include/delimiter_optarg.h"


void delimiter_optarg_nparse(const char *str, char *buffer, size_t n) {
    const char *c = str;
    size_t i = 0;
    while (*c && i < n) {
        switch (*c) {
            case '"':
                fprintf(stderr, "%s: invalid delimiter: %c", APP_NAME, *c);
                exit(EXIT_FAILURE);
            case ESC_BKSLASH:
                switch (*(c + 1)) {
                    case ESC_TAB:
                        buffer[i] = '\t';
                        n--;
                        break;
                    case ESC_BKSLASH:
                        buffer[i] = '\\';
                        n--;
                        break;
                    default:
                        fprintf(stderr, "%s: invalid escape sequence: \\%c", APP_NAME, *(c + 1));
                        exit(EXIT_FAILURE);
                }
                break;
            default:
                buffer[i] = *c;
                break;
        }
        c++;
        i++;
    }
};
