#include "../../include/scan/scan_main.h"


int scan(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <hostname> <port>\n", argv[0]);
        return 1;
    }

    udp_scan(argv[1], atoi(argv[2]));

    return 0;


}