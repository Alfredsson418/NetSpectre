#ifndef CAPTURE_OUTPUT_FORMAT_H
#define CAPTURE_OUTPUT_FORMAT_H

#include "../../include/netspectre.h"
#include "protocol_maps.h"
#include "capture_arguments.h"
#include "packet_capture.h"
#include "../other/replace.h"

void packet_header_info(const struct pcap_pkthdr *packet_header, char **format);

/*
    void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header);
        Usage:
            header: Metadata about captured packet
            packet: The frame or packet that was captured.
            arguments: The program arguments
        Return:
            Void
*/
void l2_packet_info(struct ether_header *eth, char * eth_prot, char **format);


/*
    void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header);
        Usage:
            header: Metadata about captured packet
            packet: The frame or packet that was captured.
            arguments: The program arguments
        Return:
            Void
*/
void l3_packet_info(struct iphdr *ip, char **format);

#endif