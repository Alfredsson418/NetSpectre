#include <stdio.h>
#include <time.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#include "network_device.h"

// Callback function used for pcap_loop that handles packages
void packet_handler(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet);

void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header);


int main() {
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
    
    /* Attempt to capture one packet. If there is no network traffic
      and the timeout is reached, it will return NULL */
    /*
    packet = pcap_next(handle, &packet_header);
    if (packet == NULL) {
        printf("No packet found.\n");
        return 2;
    }
    */

    pcap_loop(handle, 0, packet_handler, NULL);
    pcap_close(handle);
    free(device);

}

void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header) {
    printf("Packet capture length: %d\n", packet_header.caplen);
    printf("Packet total length %d\n", packet_header.len);
}

void packet_handler(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet) {
    print_packet_info(packet, *header);
    return;
}