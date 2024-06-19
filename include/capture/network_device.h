#ifndef NETWORK_DEVICE_H
#define NETWORK_DEVICE_H

#include "../netspectre.h"

/*
    Gives the first given network device.

    Parameters:
        None

    Return:
        Returns first device from pcap_findalldevs, else NULL.
*/
char * get_first_network_dev();

#endif