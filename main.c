#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/io.h"
#include "include/delimiter_optarg.h"


const struct option LONG_OPTS[] = {
        {"help",       no_argument,       NULL, 'h'},
        {"version",    no_argument,       NULL, 'v'},
        {"format",     required_argument, NULL, 'f'},
        {"delimiter",  required_argument, NULL, 'd'},
        {"has-header", no_argument,       NULL, 'H'},
        {"col-width",  required_argument, NULL, 'w'},
        {"wrap",       no_argument,       NULL, 'W'},
        {0,            0, 0,                    0},
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
    unsigned int _field: 6;
    /*
     * From the most significant bit to the least significant bit:
     *
     *     (5) stdin mode: Read and process text from stdin. Useful for piping commands in the shell
     *     (4) predefined format mode: User has specified that they want to use one of the formats in FORMAT_DEFS
     *     (3) custom delimiter mode: User provides a custom delimiter
     *     (2) specify if the input have a header line
     *     (1) specify if the user has provided a custom column width layout
     *     (0) specify if line-wrap is on
     *
     * Note: (4) and (3) are mutually exclusive (they can't be both TRUE).
     */
} opt_flags = {0b000000};


bool is_both_fd(struct opt_bit_field x) {
    return ((x._field & (1 << 4)) >> 4) && ((x._field & (1 << 3)) >> 3);
}

int main(int argc, char *argv[]) {
    /*
     * Arguments processing
     */
    int opt;
    const char *raw_delimiters = ",";  // Default delimiter is the comma ',' (.csv)
    while (1) {
        int longopt_index = 0;
        opt = getopt_long(argc, argv, "hvf:d:Hw:W", LONG_OPTS, &longopt_index);
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
                        opt_flags._field |= 1 << 4;
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
                opt_flags._field |= 1 << 3;
                break;
            case 'H':
                opt_flags._field |= 1 << 2;
                break;
            case 'w':
                opt_flags._field |= 1 << 1;
                break;
            case 'W':
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
        opt_flags._field |= 1 << 5;
    }
    /* End of arguments processing */


    // Generate delimiter string
    char *delimiters = calloc(strlen(raw_delimiters), sizeof(char));
    for (size_t i = 0; i < strlen(raw_delimiters); i++) delimiters[i] = '\0';
    delimiter_optarg_nparse(raw_delimiters, delimiters, strlen(raw_delimiters));


    /*
     * Main dsv processor
     */
    if ((opt_flags._field & (1 << 5)) >> 5) {  // stdin mode

        // TODO: Implement this

    } else {  // File input mode

        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
        while (optind < argc) {
            FILE *file = fopen(argv[optind], "r");
            if (file == NULL) {
                print_file_not_found(argv[optind]);
                fclose(file);
                exit(EXIT_FAILURE);
            }

            char *line = NULL;
            size_t buffer_len = 0;
            ssize_t line_len;
            while ((line_len = getline(&line, &buffer_len, file)) != -1) {
                // TODO: Implement this
                printf("%s", line);
            }
            free(line);
            fclose(file);
            optind++;
        }
        #pragma clang diagnostic pop

    }
    /* End of main dsv processor */


    free(delimiters);
    return EXIT_SUCCESS;
}
