#include "../../include/capture/packet_capture.h"

/*
    The use for this is to capture packtes that is comming to the device
    You should be able to read and see what these packages contain
*/

// Callback function for pcap_loop
void packet_handler(struct capture_arguments * arguments ,const struct pcap_pkthdr *packet_header, const unsigned char *packet) {

    /*
        sniff_ethernet 	X
        sniff_ip 	X + SIZE_ETHERNET
        sniff_tcp 	X + SIZE_ETHERNET + {IP header length}
        payload 	X + SIZE_ETHERNET + {IP header length} + {TCP header length}
    
    */
    
    // String does not change
    char * string = arguments->format;
    if (strstr(string, "\\n")) {
        string = replace_substring(string, "\\n", "\n");
    }
    if (strstr(string, "\\t")) {
        string = replace_substring(string, "\\t", "\t");
    }
    if (strstr(string, "\\v")) {
        string = replace_substring(string, "\\v", "\v");
    }

    packet_header_info(packet_header, &string);

    /*
        The size of the Ethernet header is typically 14 bytes (sizeof(struct ether_header)),
        and the size of the IP header can be calculated from the ihl field of the iphdr struct,
        which represents the header length in 32-bit words. To convert this to bytes, you multiply by 4.
    */
    struct ether_header *eth = (struct ether_header *)packet;
    char * eth_type = determine_packet_protocol(eth->ether_type, 2);
    l2_packet_info(eth, eth_type, &string);
    
    struct iphdr *ip = NULL;
    if (strcmp(eth_type, "IPv4") == 0) {
        ip = (struct iphdr *)(packet + sizeof(struct ether_header)); // Skip the Ethernet header;
    }
    
    l3_packet_info(ip, &string);

    if (arguments->hexdump) {
        unsigned char *payload = (unsigned char *)(packet + sizeof(struct ether_header) + ip->ihl*4);
        int payload_length = packet_header->len - sizeof(struct ether_header) - ip->ihl*4;
        hexdump(payload, payload_length, 16);
    }
    PRINT("%s\n", string);
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
    char errbuff[PCAP_ERRBUF_SIZE]; // Error Buffer

    // Varibles for pcap_open_live
    struct network_device * device; // Network device to fetch packages from
    int snap_len = 65663; // The maximum number of bytes to capture from each packet.
    /*
        If promisc is set to 1, the interface will be put into promiscuous mode.
        This means that all packets on the network, not just those destined
        for your machine, will be captured. 
        If set to 0, only packets destined for your machine will be captured.
    */ 
    int promisc = 1;  
    int to_ms = -1; // The read timeout in milliseconds. A value of -1 means to wait indefinitely for a packet.
    pcap_t *package_handle = NULL; // Packet capture handle

    // Varibles for pcap_loop
    int packages_count = 0; // The number of packets to process before returning. A value of -1 or 0 means to loop forever.

    // Varibles for argp
    struct capture_arguments *arguments = malloc(sizeof(struct capture_arguments));

    if (arguments == NULL) {
        ERR_PRINT("Failed to allocate memory for arguments\n", NULL);
        exit(0);
    }

    // Default values
    arguments->verbose = 0;
    arguments->format = "IPv4-SRC: {ipv4-src} | "
                        "IPv4-DST: {ipv4-dst} | "
                        "l3 protocol: {ipv4-prot}({ipv4-prot-num}) | "
                        "Captured len: {head-capture-len} | "
                        "Origin len: {head-origin-len} | "
                        "Timestamp: {head-time}";
    arguments->device = NULL;
    arguments->hexdump = 0;
    arguments->quiet = 0;
    arguments->load_pcap = NULL;

    argp_parse(&capture_argp, argc, argv, 0, 0, arguments);

    DEBUG_MESSAGE("Verbose is set to %d\n", arguments->verbose);
    DEBUG_MESSAGE("Format is set to %s\n", arguments->format);
    DEBUG_MESSAGE("Device is set to %s\n", arguments->device);
    DEBUG_MESSAGE("Hexdump is set to %d\n", arguments->hexdump);
    DEBUG_MESSAGE("Quiet is set to %d\n", arguments->quiet);
    DEBUG_MESSAGE("Load Pcap is set to %s\n", arguments->load_pcap);

    if (arguments->load_pcap != NULL) {
        PRINT("Opening pcap file: %s", arguments->load_pcap);

        package_handle = pcap_open_offline(arguments->load_pcap, errbuff);

        if (package_handle == NULL) {
            ERR_PRINT("Error opening pcap file: %s", errbuff);
            exit(0);
        }
    } else {
        if (arguments->device == NULL) {
            device = get_first_network_dev(errbuff);
            if (device == NULL) {
                ERR_PRINT("Error opening network device: %s\n", errbuff);
                exit(0);
            } else {
                arguments->device = device->name;
                DEBUG_MESSAGE("Device is changed to %s\n", arguments->device);
            }
        }
        DEBUG_MESSAGE("Trying to capture on interface: %s", device);

        package_handle = pcap_open_live(arguments->device, snap_len, promisc, to_ms, errbuff);

        if (package_handle == NULL) {
            ERR_PRINT("Error opening pcap handle: %s", errbuff);
            exit(0);
        }

        PRINT("Capture on interface: %s\n", device);

    }

    pcap_loop(package_handle, packages_count,(pcap_handler) packet_handler, (unsigned char *) arguments);
    // pcap_breakloop exists
    pcap_close(package_handle);
    free(device);
    return 0;
}
