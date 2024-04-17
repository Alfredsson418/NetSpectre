#include "../../include/capture/capture_arguments.h"

// Program documentation.
const char capture_docs[] = "Capture packets from and to your device.";



/*
    The OPTIONS field contains a pointer to a vector of struct argp_option’s;
    that structure has the following fields (if you assign your option
    structures using array initialization like this example, unspecified
    fields will be defaulted to 0, and need not be specified):
     NAME   – The name of this option’s long option (may be zero)
     KEY    – The KEY to pass to the PARSER function when parsing this option,
               *and* the name of this option’s short option, if it is a
               printable ascii character
     ARG    – The name of this option’s argument, if any
     FLAGS  – Flags describing this option; some of them are:
                 OPTION_ARG_OPTIONAL – The argument to this option is optional
                 OPTION_ALIAS        – This option is an alias for the
                                        previous option
                 OPTION_HIDDEN       – Don’t show this option in –help output
     DOC    – A documentation string for this option, shown in –help output
*/
const struct argp_option capture_options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output"},
    {"format", 'f', "FORMAT", 0, "Specifies output FORMAT for packet capturing"},
    {"log-file", 'l', "FILE", 0, "Specifies output log FILE"},
    {"device", 'd', "DEVICE", 0, "Specifies the DEVICE to capture from"},
    {"hexdump", 'x', 0, 0, "Output hexdump from package"},
    {"quiet", 'q', 0, 0, "No output to terminal"},
    { 0 }
};

struct argp capture_argp = { capture_options, capture_parse_opt, 0, capture_docs };


error_t capture_parse_opt(int key, char *arg, struct argp_state *state){
    /*  
        Get the input argument from capture_argp_parse, which we
        know is a pointer to our arguments structure.
    */
    struct capture_arguments *arguments = state->input;
    
    switch (key) {
    case 'v':
        arguments->verbose = 1;
        break;
    case 'f':
        arguments->format = arg;
        break;
    case 'l':
        arguments->log_file = arg;
        break;
    case 'd':
        arguments->device = arg;
        break;
    case 'x':
        arguments->hexdump = 1;
        break;
    case 'q':
        arguments->quiet = 1;
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
    
}