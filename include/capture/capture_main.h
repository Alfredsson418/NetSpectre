#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H



#include "../netspectre.h"
#include "capture_arguments.h"
#include "network_device.h"
#include "packet_info.h"
#include "../other/replace.h"
#include "../other/hexdump.h"





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