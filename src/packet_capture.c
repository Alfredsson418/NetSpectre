#include "../headers/packet_capture.h"

/*
    The use for this is to capture packtes that is comming to the device
    You should be able to read and see what these packages contain
*/


void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header) {
    printf("Packet capture length: %d\n", packet_header.caplen);
    printf("Packet total length %d\n", packet_header.len);
}

// Callback function for pcap_loop
void packet_handler(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet) {
    struct ether_header *eth;
    eth = (struct ether_header *)packet;
    printf("%s\n", determine_packet_protocol(eth->ether_type));
}

char * determine_packet_protocol(uint16_t packet_protocol) {
    // https://en.wikipedia.org/wiki/EtherType
    /*
        EtherType is a mechanism used at Layer 2 to facilitate the
        correct interpretation and processing of data at Layer 3.
    */
    for (int i = 0; i < sizeof(ethertype_protocol_map) / sizeof(ethertype_protocol_map[0]); i++) {
        if (ntohs(packet_protocol) == ethertype_protocol_map[i].ether_type) {
            return ethertype_protocol_map[i].protocol_name;
        }
    }
    return "Unknown";
}

// This could be handled as the main function for packet capturing
int capture() {
    char errbuff[PCAP_ERRBUF_SIZE];
    struct network_device * device = get_first_network_dev(errbuff);
    pcap_t *handle;
    int packet_count_limit = 1;
    int timeout_limit = 10000;
    const unsigned char *packet;
    struct pcap_pkthdr packet_header;

    handle = pcap_open_live(device->name, BUFSIZ, packet_count_limit, timeout_limit, errbuff);

    if (handle == NULL) {
        printf("Could not open device %s: %s\n", device ->name, errbuff);
        return 2;
    }
    

    pcap_loop(handle, 0, packet_handler, NULL);
    pcap_close(handle);
    free(device);
}