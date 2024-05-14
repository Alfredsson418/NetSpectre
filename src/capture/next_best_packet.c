#include "../../include/capture/next_best_packet.h"

int next_best_packet(struct pcap_pkthdr **packet_header, unsigned char **packet, char * network_device ,char * filter, int timeout_ms) {
    char errbuff[PCAP_ERRBUF_SIZE]; // Error Buffer
    pcap_t *package_handle = NULL;
    int snap_len = MAX_PACKET_SIZE;
    int promisc = 1;
    int net_dev_alloc = 0;

    if (network_device == NULL) {
        network_device = get_first_network_dev();
        net_dev_alloc = 1;
    }

    struct bpf_program pcap_filter;

    package_handle = pcap_open_live(network_device, snap_len, promisc, timeout_ms, errbuff);


    if (package_handle == NULL) {
        ERR_PRINT("Error opening pcap file\n", NULL);
        ERR_PRINT("%s\n", errbuff);
        return -1;
    }

    if (filter != NULL) {
        if (pcap_compile(package_handle, &pcap_filter, filter, 0, 0) == -1)  {
            ERR_PRINT("Bad filter - %s\n", pcap_geterr(package_handle));
            return -1;
        }
        if (pcap_setfilter(package_handle, &pcap_filter) == -1) {
            ERR_PRINT("Error setting filter - %s\n", pcap_geterr(package_handle));
            return -1;
        }
    }
    PRINT("SCANNING\n", NULL);
    int res = pcap_next_ex(package_handle, packet_header, packet);
    PRINT("FOUND SOMETHING\n", NULL);
    pcap_close(package_handle);
    if (net_dev_alloc) {
        free(network_device);
    } 
    return 0;
}