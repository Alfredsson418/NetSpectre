#ifndef UDP_SCAN_H
#define UDP_SCAN_H

#include "../netspectre.h"
#include "../capture/next_best_packet.h"

int udp_scan(char ip[IPV4_ADDR_STR_LEN], int port);

#endif