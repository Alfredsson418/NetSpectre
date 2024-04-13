#ifndef CAPTURE_ARGUMENTS_H
#define CAPTURE_ARGUMENTS_H

#include "../other/process_arguments.h"

static const struct argument_options capture_allowed_arguments[] = {
    {"-v", "--verbose", false, false},
    {"-f", "--format", true, false},
    {"-l", "--log-file", true, false},
    {"-d", "--device", true, false},
};

#define CAPTURE_ALLOWED_ARGUMENTS_SIZE sizeof(capture_allowed_arguments) / sizeof(capture_allowed_arguments[0])

// static const struct argument_options (*capture_arguments_ptr)[] = &capture_arguments;


static const int capture_allowed_arguments_size = CAPTURE_ALLOWED_ARGUMENTS_SIZE;

static char * capture_process_arguments[CAPTURE_ALLOWED_ARGUMENTS_SIZE];

#endif