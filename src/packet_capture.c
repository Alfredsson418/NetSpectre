#include "../headers/netspectre.h"
#include "../headers/packet_capture.h"

void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header) {
    printf("Packet capture length: %d\n", packet_header.caplen);
    printf("Packet total length %d\n", packet_header.len);
}

// Callback function for pcap_loop
void packet_handler(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet) {
    struct ether_header *eth;
    eth = (struct ether_header *)packet;
    if (ntohs(eth->ether_type) == 0x0800) { // 0x0800 is IP protocol
        printf("IP\n");
    } else if (ntohs(eth->ether_type) == 0x0806) { // 0x0806 is ARP
        printf("ARP\n");
    } else if (ntohs(eth->ether_type) == 0x86dd) { // 0x86dd is IPv6
        printf("IPv6\n");
    } else {
        printf("Unknown protocol\n");
    }
}
