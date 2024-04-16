#include "../../include/capture/capture_output.h"


void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header, struct capture_arguments * arguments) {
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

    if (strstr(arguments->format, "\\n")) {
        arguments->format = replace_substring(arguments->format, "\\n", "\n");
    }
    if (strstr(arguments->format, "\\t")) {
        arguments->format = replace_substring(arguments->format, "\\t", "\t");
    }
    if (strstr(arguments->format, "\\v")) {
        arguments->format = replace_substring(arguments->format, "\\v", "\v");
    }

    struct ether_header *eth = (struct ether_header *)packet;

    if (strstr(arguments->format, "{mac-src}") != NULL) {
        char mac[18] = {0};
        bin_to_mac(eth->ether_shost, mac);
        arguments->format = replace_substring(arguments->format, "{mac-src}", mac);
    }
    if (strstr(arguments->format, "{mac-dst}") != NULL) {
        char mac[18] = {0};
        bin_to_mac(eth->ether_dhost, mac);
        arguments->format = replace_substring(arguments->format, "{mac-dst}", mac);
    }

    char * eth_type = determine_packet_protocol(eth->ether_type, 2);

    if (strstr(arguments->format, "{mac-prot}") != NULL) {
        arguments->format = replace_substring(arguments->format, "{mac-prot}", eth_type);
    }

    if (strcmp(eth_type, "IPv4") == 0) {
        struct iphdr *ip = (struct iphdr *)(packet + sizeof(struct ether_header)); // Skip the Ethernet header;
        // printf("%s(%d) | ", determine_packet_protocol(ip->protocol, 3), ip->protocol);
        
        if (strstr(arguments->format, "{ipv4-src}") != NULL) {
            struct in_addr src_addr;
            src_addr.s_addr = ip->saddr;
            arguments->format = replace_substring(arguments->format, "{ipv4-src}", inet_ntoa(src_addr));
        }
        if (strstr(arguments->format, "{ipv4-dst}") != NULL) {
            struct in_addr dst_addr;
            dst_addr.s_addr = ip->daddr;
            arguments->format = replace_substring(arguments->format, "{ipv4-dst}", inet_ntoa(dst_addr));
        }
        char * ip_protocol = determine_packet_protocol(ip->protocol, 3);
        if (strstr(arguments->format, "{ipv4-prot}") != NULL) {
            arguments->format = replace_substring(arguments->format, "{ipv4-prot}", ip_protocol);
        }
        if (strstr(arguments->format, "{ipv4-prot-num}") != NULL) {
            char str[4];
            sprintf(str, "%d", ip->protocol);
            arguments->format = replace_substring(arguments->format, "{ipv4-prot-num}", str);
        }

        /*
            The size of the Ethernet header is typically 14 bytes (sizeof(struct ether_header)),
            and the size of the IP header can be calculated from the ihl field of the iphdr struct,
            which represents the header length in 32-bit words. To convert this to bytes, you multiply by 4.
        */
        if (arguments->hexdump) {
            unsigned char *payload = (unsigned char *)(packet + sizeof(struct ether_header) + ip->ihl*4);
            int payload_length = packet_header.len - sizeof(struct ether_header) - ip->ihl*4;
            hexdump(payload, payload_length, 16);
        }
    }
    // printf("Packet capture length: %d ", packet_header.caplen);
    // printf("Packet total length %d", packet_header.len);
    // printf("Timestamp: %ld.%06ld", packet_header.ts.tv_sec, packet_header.ts.tv_usec);
    printf("%s\n", arguments->format);
}
