#include "../include/netspectre.h"
#include "../include/capture/packet_capture.h"

/*
    This is the main file where all the "outgoing commands" are sent like scan and capture
*/


int main(int argc, char *argv[]) {
    // Always 1 or more becase name of file is first
    if (argc < 2) {
        printf("No arguments detected! Exiting! \n");
        exit(0);
    }

    // Skipping the second index so that I can pass it to argp without unknown behavior
    char *options_argv[argc - 1];
    options_argv[0] = argv[0];
    for (int i = 1; i < argc - 1; i++) {
        options_argv[i] = argv[i + 1];
    }
    int options_argc = argc - 1;

    /*
    for (int i = 0; i < options_argc; i++) {
        printf("%s\n", options_argv[i]);
    }
    */

    if (strcasecmp(argv[1], "capture") == 0) {
        capture(options_argc, options_argv);
    }else if (strcasecmp(argv[1], "scan") == 0) {
        // scan();
    } else {
        printf("Did not recognice command! Exiting! \n");
        exit(0);
    }
    
}