#include "../headers/packet_capture.h"

/*
    The use for this is to capture packtes that is comming to the device
    You should be able to read and see what these packages contain
*/


void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header) {
    /*
        unsigned char ihl: The Internet Header Length (IHL) field. This represents the length of the IP header in 32-bit words. The minimum value is 5, which corresponds to a header length of 20 bytes.
        unsigned char version: The version of the IP protocol. For IPv4, this is always 4.
        unsigned char tos: The Type of Service (ToS) field. This field is used to specify the quality of service desired for the packet.
        unsigned short tot_len: The total length of the IP packet, including the header and the data, in bytes.
        unsigned short id: An identifier to aid in assembling the fragments of a datagram.
        unsigned short frag_off: The fragment offset field, measured in units of 8-byte blocks.
        unsigned char ttl: The Time To Live (TTL) field. This field is used to limit the lifespan of a packet in the network.
        unsigned char protocol: The protocol field. This field indicates the protocol used in the payload of the IP packet.
        unsigned short check: The checksum field. This field is used for error-checking of the header.
        unsigned int saddr: The source IP address.
        unsigned int daddr: The destination IP address.
    */

    struct ether_header *eth = (struct ether_header *)packet;;
    if (strcmp(determine_packet_protocol(eth->ether_type, 2), "IPv4") == 0) {
        struct iphdr *ip = (struct iphdr *)(packet + sizeof(struct ether_header)); // Skip the Ethernet header;
        // printf("%s(%d) | ", determine_packet_protocol(ip->protocol, 3), ip->protocol);

        struct in_addr src_addr, dst_addr;
        src_addr.s_addr = ip->saddr;
        dst_addr.s_addr = ip->daddr;
        // printf("SRC IP: %s ", inet_ntoa(src_addr));
        // printf("DST IP: %s", inet_ntoa(dst_addr));

        /*
            The size of the Ethernet header is typically 14 bytes (sizeof(struct ether_header)),
            and the size of the IP header can be calculated from the ihl field of the iphdr struct,
            which represents the header length in 32-bit words. To convert this to bytes, you multiply by 4.
        */
        unsigned char *payload = (unsigned char *)(packet + sizeof(struct ether_header) + ip->ihl*4);
        int payload_length = packet_header.len - sizeof(struct ether_header) - ip->ihl*4;
        hexdump(payload, payload_length, 16);
        
    }
    // printf("Packet capture length: %d ", packet_header.caplen);
    // printf("Packet total length %d", packet_header.len);
    // printf("Timestamp: %ld.%06ld", packet_header.ts.tv_sec, packet_header.ts.tv_usec);
    printf("\n");
}

// Callback function for pcap_loop
void packet_handler(unsigned char *args,const struct pcap_pkthdr *packet_header, const unsigned char *packet) {
    print_packet_info(packet, *packet_header);

}

// Determine 
char * determine_packet_protocol(uint16_t packet_protocol, int layer) {
    // https://en.wikipedia.org/wiki/EtherType
    /*
        EtherType is a mechanism used at Layer 2 to facilitate the
        correct interpretation and processing of data at Layer 3.
        The "map" can be found in the header file
    */
    switch (layer)
    {
    case 2: // Layer 2 (Ethertype)
        for (int i = 0; i < sizeof(l2_protocol_map) / sizeof(l2_protocol_map[0]); i++) {
            // ntohs is used to get a decimal
            if (ntohs(packet_protocol) == l2_protocol_map[i].ether_type) {
                return l2_protocol_map[i].protocol_name;
            }
        }
        return "Unknown";

    case 3: // Layer 3 (IP)
        for (int i = 0; i < sizeof(l3_protocol_map) / sizeof(l3_protocol_map[0]); i++) {
            if (packet_protocol == l3_protocol_map[i].ether_type) {
                return l3_protocol_map[i].protocol_name;
            }
        }
        return "Unknown";

    default:
        return "Unknown";
    }
}

void convert_mac_from_byte(uint8_t mac_bin[6], char mac[18]) {
    /*
        "%02x" is the format specifier. The %x part means that the argument will be printed in hexadecimal.
        The 02 part means that the printed hexadecimal number will always have at least two digits.
        If the hexadecimal number is only one digit long, it will be padded with a leading zero.
        mac_bin is a field in this structure that represents the source MAC address of the packet,
        which is a 6-byte (48-bit) number. mac_bin[i] accesses the i-th byte of this address.
    */
    for(int i = 0; i < 6; ++i) {
        sprintf(&mac[i*3], "%02x", mac_bin[i]);
        if (i < 5) {
            mac[i*3 + 2] = ':';
        }
    }
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

    printf("Capture on interface: %s\n", device->name);


    struct bpf_program fp;
    char filter_exp[] = "tcp"; // filter expression

    handle = pcap_open_live(device->name, 65535, packet_count_limit, timeout_limit, errbuff);

    if (handle == NULL) {
        printf("Could not open device %s: %s\n", device->name, errbuff);
        return 2;
    }
    

    pcap_loop(handle, 0, packet_handler, NULL);
    // pcap_breakloop exists
    pcap_close(handle);
    free(device);
}