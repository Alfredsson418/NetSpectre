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

    if (strcasecmp(argv[1], "capture") == 0) {
        capture(argc, argv);
    }else if (strcasecmp(argv[1], "scan") == 0) {
        // scan();

    } else {
        printf("Did not recognice command! Exiting! \n");
        exit(0);
    }
    
}