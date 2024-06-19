#include "../../include/capture/capture_main.h"

/*
    The use for this is to capture packtes that is comming to the device
    You should be able to read and see what these packages contain
*/

pcap_t *package_handle;

void handle_sigint(int sig) { 
    PRINT("STOPPING PROGRAM!!!\n", NULL);
    pcap_breakloop(package_handle);
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


int capture(int argc, char *argv[]) {
    char errbuff[PCAP_ERRBUF_SIZE]; // Error Buffer

    // Varibles for pcap_open_live
    int snap_len = MAX_PACKET_SIZE; // The maximum number of bytes to capture from each packet.
    /*
        If promisc is set to 1, the interface will be put into promiscuous mode.
        This means that all packets on the network, not just those destined
        for your machine, will be captured. 
        If set to 0, only packets destined for your machine will be captured.
    */ 
    int promisc = 1;  
    int to_ms = -1; // The read timeout in milliseconds. A value of -1 means to wait indefinitely for a packet.
    package_handle = NULL; // Packet capture handle

    // Varibles for filtering
    struct bpf_program filter;

    // Varibles for argp
    struct capture_arguments *arguments = malloc(sizeof(struct capture_arguments));

    if (arguments == NULL) {
        ERR_PRINT("Failed to allocate memory for arguments\n", NULL);
        exit(0);
    }

    // Default values
    arguments->format = 
    "Package header: \n"
    "   Time of capture: {head-time}\n"
    "   Package Length: {head-origin-len}\n"
    "   Captured Length: {head-capture-len}\n"
    "Layer 2:\n"
    "   MAC-SRC: {mac-src}\n"
    "   MAC-DST: {mac-dst}\n"
    "   Protocol: {mac-prot}\n"
    "Layer 3:\n"
    "   IPv4-SRC: {ipv4-src}\n"
    "   IPv4-DST: {ipv4-dst}\n"
    "   Protocol: {l3-prot}({l3-prot-num})";
    arguments->hexdump = 0;
    arguments->device = NULL;
    arguments->pcap_load = NULL;
    arguments->filter = NULL;
    arguments->capture_amount = 0;

    argp_parse(&capture_argp, argc, argv, 0, 0, arguments);

    DEBUG_MESSAGE("-------OUTPUT SETTINGS-------\n", NULL);
    DEBUG_MESSAGE("Debug is set to: %d\n", g_debug_enabled);
    DEBUG_MESSAGE("Verbose is set to: %d\n", g_verbose_enabled);
    DEBUG_MESSAGE("Output is set to: %d\n", g_no_terminal_output);
    DEBUG_MESSAGE("-------ARGUMENT SETTINGS-------\n", NULL);
    DEBUG_MESSAGE("Format is set to: \n%s\n", arguments->format);
    DEBUG_MESSAGE("Device is set to: %s\n", arguments->device);
    DEBUG_MESSAGE("Output hexdump is set to: %d\n", arguments->hexdump);
    DEBUG_MESSAGE("Load Pcap is set to: %s\n", arguments->pcap_load);
    DEBUG_MESSAGE("Capture amount is set to: %d\n", arguments->capture_amount);
    if (arguments->capture_amount == 0) VERBOSE_MESSAGE("WARNING: --capture-amount is set to 0, will loop forever\n", NULL);
    


    /* Determines how to load packages */
    if (arguments->pcap_load != NULL) { /* Load pcap file */
        PRINT("Opening pcap file: %s\n", arguments->pcap_load);

        package_handle = pcap_open_offline(arguments->pcap_load, errbuff);

        if (package_handle == NULL) {
            ERR_PRINT("Error opening pcap file\n", NULL);
            DEBUG_MESSAGE("%s\n", errbuff);
            exit(0);
        }
    } else { /* Packages though network device */
        if (arguments->device == NULL) {
            arguments->device = get_first_network_dev();
            if (arguments->device == NULL) {
                ERR_PRINT("Found no network device\n", NULL);
                exit(0);
            } else {
                DEBUG_MESSAGE("Device was not set, first found is %s\n", arguments->device);
            }
        }
        DEBUG_MESSAGE("Trying to capture on interface: %s\n", arguments->device);

        package_handle = pcap_open_live(arguments->device, snap_len, promisc, to_ms, errbuff);

        if (package_handle == NULL) {
            ERR_PRINT("Error opening pcap handle: %s\n", errbuff);
            exit(0);
        }

        PRINT("Capture on interface: %s\n", arguments->device);

    }

    // Capturing CTRL C
    signal(SIGINT, handle_sigint);


    /* Filtering */
    if (arguments->filter != NULL) {
        VERBOSE_MESSAGE("Compiling filter: %s\n", arguments->filter); 
        if (pcap_compile(package_handle, &filter, arguments->filter, 0, 0) == -1) {
            ERR_PRINT("Bad filter - %s\n", pcap_geterr(package_handle));
            return 2;
        }
        VERBOSE_MESSAGE("Filter compiled!\n", NULL);

        VERBOSE_MESSAGE("Adding filter...\n", NULL);
        if (pcap_setfilter(package_handle, &filter) == -1) {
            ERR_PRINT("Error setting filter - %s\n", pcap_geterr(package_handle));
            return 2;
        }
        VERBOSE_MESSAGE("Filter added!\n", NULL);
    } else {
        VERBOSE_MESSAGE("No filters found, skipping filter compiling\n", NULL);
    }

    PRINT("Press CTRL+C to exit capture\n", NULL);

    pcap_loop(package_handle, arguments->capture_amount,(pcap_handler) packet_handler, (unsigned char *) arguments);

    
    DEBUG_MESSAGE("Freeing varibles...\n", NULL);
    pcap_close(package_handle);
    free(arguments->device);
    free(arguments);
    DEBUG_MESSAGE("Varibles freed!\n", NULL);

    return 0;
}
