#ifndef PACKET_INFO_H
#define PACKET_INFO_H

#include "../../include/netspectre.h"
#include "protocol_maps.h"
#include "capture_arguments.h"
#include "capture_main.h"
#include "../other/replace.h"

/*
    void packet_handler(unsigned char *args,const struct pcap_pkthdr *packet_header, const unsigned char *packet);
        Usage:
            args:    The args parameter is used to pass data that was specified when the packet handler
                        function was registered with pcap_loop or pcap_dispatch.
                        This could be any type of data that you want to have available
                        in your packet handler function.
            packet_header: Metadata about captured packet
            packet: The frame or packet that was captured.
            arguments: The program arguments
        Return:
            Void
*/
void packet_handler(struct capture_arguments * arguments , const struct pcap_pkthdr *packet_header, const unsigned char *packet);


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
void l2_packet_info(const unsigned char *packet, char **format);


/*
    void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header);
        Usage:
            header: Metadata about captured packet
            packet: The frame or packet that was captured.
            arguments: The program arguments
        Return:
            Void
*/
void l3_packet_info(const unsigned char *packet, char **format);

#endif