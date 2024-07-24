// Compiled on Linux (x86_64)
// Author: giraffe
// Kernel: 6.9.6-arch1-1
// Date: 2024-07-04 11:44:36
// File: gwc.c
// Compiler: gcc (gcc (GCC) 14.1.1 20240522)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <argp.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

// Structure to hold the program arguments
struct arguments {
    int lines;
    int words;
    int chars;
    char **files;
    int file_count;
};

// Function to count lines, words, and characters in a file
void count_file(FILE *file, int *lines, int *words, int *chars) {
    wint_t wch;
    int in_word = 0;

    *lines = *words = *chars = 0;

    while ((wch = fgetwc(file)) != WEOF) {
        (*chars)++;
        //printf("Read wchar: %lc\n", wch); // Debugging output

        if (wch == L'\n') {
            (*lines)++;
        }

        if (iswspace(wch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            (*words)++;
        }
    }
}

// Argp option definition
static struct argp_option options[] = {
    { "lines", 'l', 0, 0, "Print the newline counts" },
    { "words", 'w', 0, 0, "Print the word counts" },
    { "chars", 'c', 0, 0, "Print the character counts" },
    { 0 }
};

// Argp parser function
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'l':
            arguments->lines = 1;
            break;
        case 'w':
            arguments->words = 1;
            break;
        case 'c':
            arguments->chars = 1;
            break;
        case ARGP_KEY_ARG:
            arguments->files = &state->argv[state->next - 1];
            arguments->file_count = state->argc - state->next + 1;
            state->next = state->argc;
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 0) {
                argp_usage(state);
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// Argp documentation
static char args_doc[] = "[FILE]...";
static char doc[] = "Custom wc implementation by Goofygiraffe06";

// Argp parser configuration
static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char *argv[]) {
    struct arguments arguments;
    FILE *file;
    int lines, words, chars;

    // Initialize default values
    arguments.lines = 0;
    arguments.words = 0;
    arguments.chars = 0;
    arguments.files = NULL;
    arguments.file_count = 0;

    // Set locale for multibyte character support
    setlocale(LC_ALL, "");

    // Parse arguments
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // Default to printing all counts if no specific option is provided
    if (!arguments.lines && !arguments.words && !arguments.chars) {
        arguments.lines = arguments.words = arguments.chars = 1;
    }

    // If no files are provided, read from standard input
    if (arguments.file_count == 0) {
        count_file(stdin, &lines, &words, &chars);
        if (arguments.lines) printf("%d ", lines);
        if (arguments.words) printf("%d ", words);
        if (arguments.chars) printf("%d ", chars);
        printf("\n");
        return 0;
    }

    // Process each file provided
    for (int i = 0; i < arguments.file_count; i++) {
        if (strcmp(arguments.files[i], "-") == 0) {
            file = stdin;
        } else {
            file = fopen(arguments.files[i], "r");
            if (file == NULL) {
                fprintf(stderr, "Error: Cannot open file '%s'\n", arguments.files[i]);
                continue;
            }
        }

        count_file(file, &lines, &words, &chars);
        if (file != stdin) {
            fclose(file);
        }

        if (arguments.lines) printf("%d ", lines);
        if (arguments.words) printf("%d ", words);
        if (arguments.chars) printf("%d ", chars);
        sprintf("%s\n", arguments.files[i]);
    }

    return 0;
}

