#ifndef NEXT_BEST_PACKET_H
#define NEXT_BEST_PACKET_H

#include "../netspectre.h"
#include "network_device.h"

int next_best_packet(struct pcap_pkthdr **packet_header, unsigned char **packet, char * network_device ,char * filter, int timeout_ms);


#endif