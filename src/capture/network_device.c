#include "../../include/capture/network_device.h"

char * get_first_network_dev() {
    pcap_if_t *all_devices = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs(&all_devices, errbuf) == -1) {
        ERR_PRINT("Error finding devices\n", NULL);
        DEBUG_MESSAGE("pcap_findalldevs failed\n", NULL);
        exit(0);
    }
    
    if (all_devices == NULL) {
        ERR_PRINT("No network devices found\n", NULL);
        exit(0);
    }

    char *dev_string = NULL;
    if (all_devices->name != NULL) {
        dev_string = calloc(strlen(all_devices->name) + 1, sizeof(char));
        if (dev_string == NULL) {
            ERR_PRINT("Memory allocation failed\n", NULL);
            exit(0);
        }
        strncpy(dev_string, all_devices->name, strlen(all_devices->name));
    }

    pcap_freealldevs(all_devices);

    return dev_string;
}