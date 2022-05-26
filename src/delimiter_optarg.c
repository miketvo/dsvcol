//
// Created by miketvo on 5/24/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "../include/glob.h"
#include "../include/util.h"
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
                        if (!ischrin('\t', buffer, i)) {
                            buffer[i] = '\t';
                            i++;
                        }
                        c++;
                        n--;
                        break;
                    case ESC_BKSLASH:
                        if (!ischrin('\\', buffer, i)) {
                            buffer[i] = '\\';
                            i++;
                        }
                        c++;
                        n--;
                        break;
                    default:
                        fprintf(stderr, "%s: invalid escape sequence: \\%c", APP_NAME, *(c + 1));
                        exit(EXIT_FAILURE);
                }
                break;
            default:
                if (!ischrin(*c, buffer, i)) {
                    buffer[i] = *c;
                    i++;
                }
                break;
        }
        c++;
    }
};
