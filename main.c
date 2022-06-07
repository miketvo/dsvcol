#include <stdlib.h>
#include <unistd.h>  // ssize_t - Some compilers need this, some don't
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "include/util.h"
#include "include/getline.h"
#include "include/dsv.h"
#include "include/delimiter_optarg.h"


const struct option LONG_OPTS[] = {
        {"help",           no_argument,       NULL, 'h'},
        {"version",        no_argument,       NULL, 'v'},
        {"format",         required_argument, NULL, 'f'},
        {"delimiters",     required_argument, NULL, 'd'},
        {"text-qualifier", required_argument, NULL, 't'},
        {"has-header",     no_argument,       NULL, 'H'},
        {"col-width",      required_argument, NULL, 'w'},
        {"wrap",           no_argument,       NULL, 'W'},
        {"greedy",         no_argument,       NULL, 'g'},
        {0,                0, 0,                    0},
};

const char *FORMAT_DEFS[] = {
        "csv",
        "tsv",
};

const char *FORMAT_DELS[] = {
        ",",
        "\t",
};


struct opt_bit_field {
    unsigned int _field: 8;
    /*
     * From the most significant bit to the least significant bit:
     *
     *     (7) stdin mode: Read and process text from stdin. Useful for piping commands in the shell
     *     (6) predefined format mode: User has specified that they want to use one of the formats in FORMAT_DEFS
     *     (5) custom delimiter mode: User provides a custom delimiter (default is comma - csv)
     *     (4) custom text qualifier mode: User provides a custom text qualifier (default is double quote '"')
     *     (3) specify if the input have a header line
     *     (2) specify if the user has provided a custom column width layout
     *     (1) specify if line-wrap is on
     *     (0) specify if greedy mode is on (treat consecutive delimiters as one)
     *
     * Note: (6) and (5) are mutually exclusive (they can't be both TRUE).
     */
} opt_flags = {0b00000000};


bool is_both_fd(struct opt_bit_field x) {
    return ((x._field & (1 << 6)) >> 6) && ((x._field & (1 << 5)) >> 5);
}

bool is_wrap(struct opt_bit_field x) {
    return (bool) (x._field & (1 << 1)) >> 1;
}

bool is_greedy_mode(struct opt_bit_field x) {
    return (bool) x._field & 1;
}

bool is_stdin_mode(struct opt_bit_field x) {
    return (bool) (x._field & (1 << 7)) >> 7;
}


int main(int argc, char *argv[]) {
    /*
     * Arguments processing
     */
    int opt;
    const char *raw_delimiters = ",";  // Default delimiter is the comma ',' (.csv)
    char *text_qualifier = "\"\"";  // Default to double quote '"'
    const char *w_config = "auto";  // Default to left aligned columns of equal widths
    while (1) {
        int longopt_index = 0;
        opt = getopt_long(argc, argv, "hvf:d:t:Hw:Wg", LONG_OPTS, &longopt_index);
        if (opt == -1) break;

        switch (opt) {
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
            case 'f': {
                bool is_valid_optarg = false;
                for (size_t i = 0; i < sizeof(FORMAT_DEFS) / sizeof(FORMAT_DEFS[0]); i++) {
                    if (strcasecmp(optarg, FORMAT_DEFS[i]) == 0) {
                        is_valid_optarg = true;
                        raw_delimiters = FORMAT_DELS[i];
                        opt_flags._field |= 1 << 6;
                    }
                }

                if (!is_valid_optarg) {
                    print_optarg_error(optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 'd':
                raw_delimiters = optarg;
                opt_flags._field |= 1 << 5;
                break;
            case 't':
                // optarg can have at most 2 characters: one for the opening qualifier and one for the closing qualifier
                if (strlen(optarg) > 2) {
                    print_text_qualifer_optarg_error(optarg);
                    exit(EXIT_FAILURE);
                }
                text_qualifier = optarg;

                // If user input only 1 character, assume the opening and closing qualifier are the same character
                if (strlen(text_qualifier) == 1) {
                    strncat(text_qualifier, text_qualifier, 1);
                }
                opt_flags._field |= 1 << 4;
                break;
            case 'H':
                opt_flags._field |= 1 << 3;
                break;
            case 'w':
                opt_flags._field |= 1 << 2;
                w_config = optarg;
                break;
            case 'W':
                opt_flags._field |= 1 << 1;
                break;
            case 'g':
                opt_flags._field |= 1;
                break;
            default: /* '?' */
                print_bad_usage();
                exit(EXIT_FAILURE);
        }
    }

    // Guard clause for -f and -d exclusivity
    if (is_both_fd(opt_flags)) {
        fprintf(
                stderr,
                "-f (--format) and -d (--delimiter) options are mutually exclusive.\n"
        );
        print_bad_usage();
        exit(EXIT_FAILURE);
    }

    // Detect stdin mode
    if (optind == argc) {
        opt_flags._field |= 1 << 7;
    }
    /* End of arguments processing */


    /*
     * Delimiter processor
     */
    char *delimiters = calloc(strlen(raw_delimiters) + 1, sizeof(char));
    for (size_t i = 0; i < strlen(raw_delimiters); i++) delimiters[i] = '\0';
    delimiter_optarg_nparse(raw_delimiters, delimiters, strlen(raw_delimiters));

    // Guard clause for opening text-qualifier collision with delimiters
    if (ischrin(text_qualifier[0], delimiters, strlen(delimiters))) {
        print_text_qualifer_collision(text_qualifier[0]);

        // Guard clause for closing text-qualifier collision with delimiters
        if (ischrin(text_qualifier[1], delimiters, strlen(delimiters))) {
            print_text_qualifer_collision(text_qualifier[1]);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    }
    /* End of Delimiter processor */


    /*
     * Main dsv processor
     */
    char *line = NULL;
    size_t buffer_len = 0;
    ssize_t line_len;
    size_t line_count = 0;
    enum dsverr dsverrcode;
    if (is_stdin_mode(opt_flags)) {  // stdin mode

        while ((line_len = getline(&line, &buffer_len, stdin)) != -1) {
            line_count++;
            dsverrcode = dsv_printrow(
                    line, line_len,
                    w_config, delimiters, text_qualifier,
                    is_wrap(opt_flags), is_greedy_mode(opt_flags)
            );  // TODO: Implement support for wide string
            if (dsverrcode != DSV_NOERR) {
                print_dsverr(dsverrcode, line_count);
                free(line);
                exit(EXIT_FAILURE);
            }
        }
        free(line);

    } else {  // File input mode

        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
        while (optind < argc) {
            FILE *file = fopen(argv[optind], "r");
            if (file == NULL) {
                print_file_not_found(argv[optind], strerror(errno));
                exit(EXIT_FAILURE);
            }

            while ((line_len = getline(&line, &buffer_len, file)) != -1) {
                line_count++;
                dsverrcode = dsv_printrow(
                        line, line_len,
                        w_config, delimiters, text_qualifier,
                        is_wrap(opt_flags), is_greedy_mode(opt_flags)
                );  // TODO: Implement support for wide string
                if (dsverrcode != DSV_NOERR) {
                    print_dsverr(dsverrcode, line_count);
                    free(line);
                    exit(EXIT_FAILURE);
                }
            }
            free(line);
            fclose(file);
            optind++;
        }
        #pragma clang diagnostic pop

    }
    /* End of Main dsv processor */


    free(delimiters);
    return EXIT_SUCCESS;
}
