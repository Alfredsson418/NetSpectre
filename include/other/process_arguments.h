#ifndef PROCESS_ARGUMENTS_H
#define PROCESS_ARGUMENTS_H

#include "../netspectre.h"

struct argument_options {
    char * flag; // e.g -f
    char * extended_flag; // e.g --format
    bool needs_value; // If there should be anything additional afterwards
};

void process_arguments(int argc, char *argv[], const int arguments_size, const struct argument_options arguments[]);


#endif /* PROCESS_ARGUMENTS_H */

