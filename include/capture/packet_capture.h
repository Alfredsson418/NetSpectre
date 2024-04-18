#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H



#include "../netspectre.h"
#include "capture_arguments.h"
#include "network_device.h"
#include "capture_format.h"
#include "../other/replace.h"
#include "../other/hexdump.h"



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


/*
    void convert_mac_from_byte(uint8_t mac_bin[6], char mac[18]);
        Usage:
            mac_bin: Mac address in representet in binary
            mac: The function writes the MAC address to this varible
        Return:
            Void
*/
void bin_to_mac(uint8_t mac_bin[6], char mac[18]);

/*
    int capture();
        Usage:
            Used as the main function to capture packets
*/
int capture(int argc, char *argv[]);

#endif