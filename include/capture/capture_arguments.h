#ifndef CAPTURE_ARGUMENTS_H
#define CAPTURE_ARGUMENTS_H

#include "../other/process_arguments.h"

static const struct argument_options capture_arguments[] = {
    {"-v", "--verbose", false},
    {"-f", "--format", true},
    {"-l", "--log-file", true},
};

// static const struct argument_options (*capture_arguments_ptr)[] = &capture_arguments;


static const int capture_arguments_size = sizeof(capture_arguments) / sizeof(capture_arguments[0]);

#endif