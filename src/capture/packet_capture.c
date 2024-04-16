#include "../../include/capture/packet_capture.h"

/*
    The use for this is to capture packtes that is comming to the device
    You should be able to read and see what these packages contain
*/

// Callback function for pcap_loop
void packet_handler(struct capture_arguments * arguments ,const struct pcap_pkthdr *packet_header, const unsigned char *packet) {
    print_packet_info(packet, *packet_header, arguments);

}

void bin_to_mac(uint8_t mac_bin[6], char mac[18]) {
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
int capture(int argc, char *argv[]) {
    struct capture_arguments arguments;

    // Default values
    arguments.verbose = 0;
    arguments.format = NULL;
    arguments.log_file = NULL;
    arguments.device = NULL;
    arguments.hexdump = 0;

    argp_parse(&capture_argp, argc, argv, 0, 0, &arguments);

    // printf("Verbose: %d \n Format: %s\n Log File: %s\n Device: %s", argument.verbose, argument.format, argument.log_file, argument.device);


    
    char errbuff[PCAP_ERRBUF_SIZE];
    struct network_device * device = get_first_network_dev(errbuff);
    pcap_t *handle;
    int packet_count_limit = 1;
    int timeout_limit = 10000;
    const unsigned char *packet;
    struct pcap_pkthdr packet_header;

    printf("Capture on interface: %s\n", device->name);

    handle = pcap_open_live(device->name, 65535, packet_count_limit, timeout_limit, errbuff);

    if (handle == NULL) {
        printf("Could not open device %s: %s\n", device->name, errbuff);
        return 2;
    }
    

    pcap_loop(handle, 0, (pcap_handler)packet_handler, (unsigned char*)&arguments);
    // pcap_breakloop exists
    pcap_close(handle);
    free(device);

    return 0;
    
}
