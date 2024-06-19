#ifndef NEXT_BEST_PACKET_H
#define NEXT_BEST_PACKET_H

#include "../netspectre.h"
#include "network_device.h"

net_packet * next_best_packet(char * network_device ,char * filter, int timeout);


#endif