#ifndef NETWORK_DEVICE_H
#define NETWORK_DEVICE_H

#include "../netspectre.h"

/*
    get_first_network_dev(char errbuff[PCAP_ERRBUF_SIZE]);
        Usage:
            errbuff:    the address to error message.
        Return:
            Returns first device from pcap_findalldevs, else NULL
*/
char * get_first_network_dev();

#endif