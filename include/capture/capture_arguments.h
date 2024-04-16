#ifndef CAPTURE_ARGUMENTS_H
#define CAPTURE_ARGUMENTS_H

#include "../../include/netspectre.h"

extern const struct argp_option capture_options[];

struct capture_arguments {
    int verbose;
    char * format;
    char * log_file;
    char * device;
    int hexdump;
};
/*
    error_t capture_parse_opt(int key, char *arg, struct argp_state *state);
    
    Used as an callback function in argp_parse
*/
error_t capture_parse_opt(int key, char *arg, struct argp_state *state);

extern struct argp capture_argp;

#endif