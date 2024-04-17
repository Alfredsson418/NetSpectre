#include "../../include/capture/packet_capture.h"

/*
    The use for this is to capture packtes that is comming to the device
    You should be able to read and see what these packages contain
*/

// Callback function for pcap_loop
void packet_handler(struct capture_arguments * arguments ,const struct pcap_pkthdr *packet_header, const unsigned char *packet) {
    // String does not change
    char * string = arguments->format;
    if (strstr(string, "\\n")) {
        replace_substring(string, "\\n", "\n");
    }
    if (strstr(string, "\\t")) {
        replace_substring(string, "\\t", "\t");
    }
    if (strstr(string, "\\v")) {
        replace_substring(string, "\\v", "\v");
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
    printf("%s\n", string);
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
    struct capture_arguments *arguments = malloc(sizeof(struct capture_arguments));
    if (arguments == NULL) {
        printf("Failed to allocate memory for arguments\n");
        return -1;
    }

    // Default values
    arguments->verbose = 0;
    arguments->format = "IPv4-SRC: {ipv4-src} | "
                        "IPv4-DST: {ipv4-dst} | "
                        "l3 protocol: {ipv4-prot}({ipv4-prot-num}) | "
                        "Captured len: {head-capture-len} | "
                        "Origin len: {head-origin-len} | "
                        "Timestamp: {head-time}";
    arguments->log_file = NULL;
    arguments->device = NULL;
    arguments->hexdump = 0;
    arguments->quiet = 0;

    argp_parse(&capture_argp, argc, argv, 0, 0, arguments);

    // printf("Verbose: %d \n Format: %s\n Log File: %s\n Device: %s", argument.verbose, argument.format, argument.log_file, argument.device);


    
    char errbuff[PCAP_ERRBUF_SIZE];
    struct network_device * device = get_first_network_dev(errbuff);
    pcap_t *decsr;
    int packet_count_limit = 1;
    int timeout_limit = -1;
    struct bpf_program fp;        /* to hold compiled program */
    bpf_u_int32 pNet;             /* ip address*/
    bpf_u_int32 pMask;            /* subnet mask */

    printf("Capture on interface: %s\n", device->name);

    // fetch the network address and network mask
    pcap_lookupnet("wlp61s0", &pNet, &pMask, errbuff);

    decsr = pcap_open_live("wlp61s0", BUFSIZ, 0, -1, errbuff);

    if (decsr == NULL) {
        printf("Could not open device %s: %s\n", device->name, errbuff);
        return 2;
    }
    /*
    // Compile the filter expression
    if(pcap_compile(decsr, &fp, "tcp", 0, &pMask) == -1)
    {
        printf("\npcap_compile() failed\n");
        return -1;
    }

        // Set the filter compiled above
    if(pcap_setfilter(decsr, &fp) == -1)
    {
        printf("\npcap_setfilter() failed\n");
        exit(1);
    }
    */

    pcap_loop(decsr, 0, packet_handler, (char *) arguments);
    // pcap_breakloop exists
    pcap_close(decsr);
    free(device);

    return 0;
    
}
