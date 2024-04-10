#ifndef NETWORK_DEVICE_H
#define NETWORK_DEVICE_H

#include "../netspectre.h"

struct network_device {
    char name[100];
    char IPv4[INET_ADDRSTRLEN];
    char subnet_mask[INET_ADDRSTRLEN];
    char IPv6[INET6_ADDRSTRLEN];
};

/*
    get_first_network_dev(char errbuff[PCAP_ERRBUF_SIZE]);
        Usage:
            errbuff:    the address to error message.
        Return:
            Returns first device from pcap_findalldevs, else NULL
*/
struct network_device * get_first_network_dev(char errbuff[PCAP_ERRBUF_SIZE]);

#endif