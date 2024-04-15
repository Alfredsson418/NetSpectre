#ifndef CAPTURE_OUTPUT_FORMAT_H
#define CAPTURE_OUTPUT_FORMAT_H

#include "../../include/netspectre.h"
#include "../other/hexdump.h"
#include "protocol_maps.h"
#include "capture_arguments.h"
#include "../other/replace_substring.h"

/*
    void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header);
        Usage:
            header: Metadata about captured packet
            packet: The frame or packet that was captured.
            arguments: The program arguments
        Return:
            Void
*/
void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header, struct capture_arguments * arguments);

#endif