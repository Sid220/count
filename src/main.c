#include <stdlib.h>
#include <argp.h>
#include "../include/count.h"
#include <unistd.h>

/* Program documentation. */

const char *argp_program_version =
        "count 1.0";
const char *argp_program_bug_address =
        "<lafakeslimshady@gmail.com>";

static char doc[] =
        "count -- count the files in a directory ([DIR...], otherwise current working directory)";

static char args_doc[] = "[DIR...]";

/* options */
static struct argp_option options[] = {
        {"output", 'o', "FILE", 0,
                "Output to FILE instead of standard output"},
        {"hidden", 'h', 0,      0,
                "Include hidden files in count"},
        {"dir",    'd', 0,      0,
                "Include directories count"},
        {"link",   'l', 0, 0, "Include symbolic links in count"},
        {0}
};

struct arguments {
    int hidden;
    int dirs;
    int links;
    char *output_file;
    unsigned int argc;
    char *args[];                /* Director(ies) */
};

/* Parse function */
static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'o':
            arguments->output_file = arg;
            break;
        case 'h':
            arguments->hidden = 1;
            break;
        case 'd':
            arguments->dirs = 1;
            break;
        case 'l':
            arguments->links = 1;
            break;
        case ARGP_KEY_ARG:
            arguments->args[state->arg_num] = arg;
            arguments->argc = state->arg_num + 1;
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/* argp parser. */
static struct argp argp = {options, parse_opt, args_doc, doc};

char *get_current_dir();

int
main(int argc, char **argv) {
    struct arguments arguments;

    /* Default values. */
    arguments.hidden = 0;
    arguments.output_file = NULL;
    arguments.dirs = 0;
    arguments.links = 0;
    arguments.args[0] = NULL;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // Not set in default values in case command is called from non-existent directory
    if(arguments.args[0] == NULL) {
        arguments.args[0] = get_current_dir();
        arguments.argc = 1;
    }

    int count = 0;
    for(int i = 0; i < arguments.argc; i++) {
        int new_count = count_query(arguments.args[i], arguments.hidden, 1, arguments.dirs, arguments.links);
        if (new_count == -1) {
            printf("count: Failed to open folder '%s'\n", arguments.args[i]);
            exit(1);
        }
        count += new_count;
    }

    if (arguments.output_file == NULL) {
        printf("%i\n", count);
    } else {
        FILE *fp = fopen(arguments.output_file, "w");
        if (fp == NULL) {
            printf("count: Failed to open output file '%s'\n", arguments.output_file);
            exit(2);
        }
        fprintf(fp, "%d\n", count);
        fclose(fp);
    }

    exit(0);
}

char *get_current_dir() {
    static char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        return cwd;
    else {
        perror("getcwd() error");
        exit(1);
    }
}
