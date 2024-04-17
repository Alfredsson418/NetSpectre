#include "../../include/capture/capture_format.h"

void packet_header_info(const struct pcap_pkthdr *packet_header, char **format) {
    
    char time_sec[20]; // Enough for a timestamp
    char origin_len[20]; // Enough for an int
    char capture_len[20]; // Enough for an int

    sprintf(time_sec, "%ld.%02ld", packet_header->ts.tv_sec, packet_header->ts.tv_usec);
    sprintf(origin_len, "%d", packet_header->len);
    sprintf(capture_len, "%d", packet_header->caplen);


    replace_format(format, "{head-capture-len}", capture_len);
    replace_format(format, "{head-origin-len}", origin_len);
    replace_format(format, "{head-time}", time_sec);

    

    // printf("Packet capture length: %d  ", packet_header->caplen);
    // printf("Packet total length %d  ", packet_header->len);
    // printf("Timestamp: %ld.%06ld  \n", packet_header->ts.tv_sec, packet_header->ts.tv_usec);
}


void l2_packet_info(struct ether_header *eth, char * eth_prot, char **format) {
    char mac_src[18] = {0};
    char mac_dst[18] = {0};
    
    if (eth != NULL) {
        bin_to_mac(eth->ether_dhost, mac_dst);
        bin_to_mac(eth->ether_shost, mac_src);
    }

    replace_format(format, "{mac-src}", mac_src);
    replace_format(format, "{mac-dst}", mac_dst);
    replace_format(format, "{mac-prot}", eth_prot);
    
}

void l3_packet_info(struct iphdr *ip, char **format) {
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
    struct in_addr src_addr, dst_addr;
    char str[4] = {0};
    char *ip_protocol = NULL;
    if (ip != NULL) {
        src_addr.s_addr = ip->saddr;
        dst_addr.s_addr = ip->daddr;
        ip_protocol = determine_packet_protocol(ip->protocol, 3);
        sprintf(str, "%d", ip->protocol);
    } 
    
    replace_format(format, "{ipv4-src}", inet_ntoa(src_addr));
    replace_format(format, "{ipv4-dst}", inet_ntoa(dst_addr));
    replace_format(format, "{ipv4-prot}", ip_protocol);
    replace_format(format, "{ipv4-prot-num}", str);
}

