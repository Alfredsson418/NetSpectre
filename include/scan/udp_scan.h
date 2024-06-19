#ifndef UDP_SCAN_H
#define UDP_SCAN_H

#include "../netspectre.h"
#include "../capture/next_best_packet.h"

/*
    Parameters:
        ip: The target to scan.
        port: The port to scan.
        timeout: Timeout in sec, will affect scanning.
    Return:
        If run successfully
*/
int udp_scan(char ip[IPV4_ADDR_STR_LEN], int port, int timeout);

#endif