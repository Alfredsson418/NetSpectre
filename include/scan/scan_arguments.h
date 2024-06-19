#ifndef SCAN_ARGUMENTS_H
#define SCAN_ARGUMENTS_H

#include "../../include/netspectre.h"

extern const struct argp_option scan_options[];

/*
    0x11 UDP
    0x06 TCP
*/

struct scan_arguments {
    char * device;
    int * ports;
    int ports_len;
    char * ports_format;
    char * target;
    char * scan_protocol;
    int timeout;
};

error_t scan_parse_opt(int key, char *arg, struct argp_state *state);

extern struct argp scan_argp;

#endif