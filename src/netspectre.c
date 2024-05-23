#include "../include/netspectre.h"
#include "../include/capture/capture_main.h"
#include "../include/scan/scan_main.h"

/*
    This is the main file where all the "outgoing commands" are sent like scan and capture
*/


int main(int argc, char *argv[]) {
    // Always 1 or more becase name of file is first
    if (argc < 2) {
        ERR_PRINT("No arguments detected! Exiting! \n", NULL);
        exit(0);
    }
    
    // Create a new array to store the merged strings
    char *processed_argv[argc - 1];

    /*
        Merge the first and second arguments into the format "%s %s"
        The merge is nessesary because to show the help and usage command correctly for argp
    */
    char *merged_string = malloc(strlen(argv[0]) + strlen(argv[1]) + 2);
    sprintf(merged_string, "%s %s", argv[0], argv[1]);

    // Store the merged string in the new array
    processed_argv[0] = merged_string;

    // Copy the remaining arguments to the new array
    for (int i = 2; i < argc; i++) {
        processed_argv[i - 1] = argv[i];
    }

    if (strcasecmp(argv[1], "capture") == 0) {
        capture(argc -1, processed_argv);
    }else if (strcasecmp(argv[1], "scan") == 0) {
        scan(argc -1, processed_argv);
    }else if (strcasecmp(argv[1], "test") == 0) {
        int * ports = NULL;
        int port_len;
        char str[] = "22,23,33-34,22-44,22";
        port_len = parse_ports(str, &ports);
        for (int i = 0; i < port_len; i++) {
            printf("%d\n", ports[i]);
        }
        free(ports);
    } else {
        ERR_PRINT("Did not recognice command! Exiting! \n", NULL);
        exit(0);
    }

    free(merged_string);

    return 0;
    
}