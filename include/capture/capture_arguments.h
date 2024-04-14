#ifndef CAPTURE_ARGUMENTS_H
#define CAPTURE_ARGUMENTS_H

#include "../../include/netspectre.h"

extern const struct argp_option capture_options[];

struct capture_arguments {
    int verbose;
    char * format;
    char * log_file;
    char * device;
};

/* Parse a single option. */
error_t capture_parse_opt(int key, char *arg, struct argp_state *state);

extern struct argp capture_argp;

#endif