#ifndef SCAN_ARGUMENTS_H
#define SCAN_ARGUMENTS_H

#include "../../include/netspectre.h"

extern const struct argp_option scan_options[];

struct scan_arguments {
    char * device;
    int * ports;
    char * target;
    int scan_protocol;
};

error_t scan_parse_opt(int key, char *arg, struct argp_state *state);

extern struct argp scan_argp;

#endif