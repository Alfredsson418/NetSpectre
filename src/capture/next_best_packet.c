#include "../../include/capture/next_best_packet.h"


typedef struct {
    int timeout;
    pcap_t * handle;
    int running;
} timeout_arg;

void * sleep_timeout(void * args) {
    timeout_arg * arg = (timeout_arg *) args;
    arg->running = 1;
    sleep(arg->timeout);
    if (arg->handle != NULL) {
        pcap_breakloop(arg->handle);
        PRINT("CANCEL\n", NULL);
    }   
    arg->running = 0;
}

typedef struct {
    struct pcap_pkthdr ** packet_header;
    unsigned char ** packet;
} loop_back_arg;

void loop_back(loop_back_arg * arg ,const struct pcap_pkthdr *packet_header, const unsigned char *packet) {

    // We need to copy the value, not the pointer
    **(arg->packet) = *packet;
    **(arg->packet_header) = *packet_header;

    PRINT("FOUND SOMETHING\n", NULL);

}


int next_best_packet(struct pcap_pkthdr **packet_header, unsigned char **packet, char * network_device ,char * filter, int timeout) {
    char errbuff[PCAP_ERRBUF_SIZE]; // Error Buffer
    pcap_t *package_handle = NULL;
    int snap_len = MAX_PACKET_SIZE;
    int promisc = 1;
    int net_dev_alloc = 0;

    if (network_device == NULL) {
        network_device = get_first_network_dev();
        net_dev_alloc = 1;
    }

    struct bpf_program pcap_filter;
    
    package_handle = pcap_open_live(network_device, snap_len, promisc, 500, errbuff);

    if (package_handle == NULL) {
        ERR_PRINT("Error opening pcap file\n", NULL);
        ERR_PRINT("%s\n", errbuff);
        return -1;
    }
    if (filter != NULL) {
        if (pcap_compile(package_handle, &pcap_filter, filter, 0, 0) == -1)  {
            ERR_PRINT("Bad filter - %s\n", pcap_geterr(package_handle));
            return -1;
        }
        if (pcap_setfilter(package_handle, &pcap_filter) == -1) {
            ERR_PRINT("Error setting filter - %s\n", pcap_geterr(package_handle));
            return -1;
        }
    }

    loop_back_arg return_arg;

    return_arg.packet = packet;
    return_arg.packet_header = packet_header;


    pthread_t thread_id;

    timeout_arg timeout_args;
    timeout_args.timeout = timeout;
    timeout_args.handle = package_handle;
    if (pthread_create(&thread_id, NULL, sleep_timeout, &timeout_args) != 0) {
        ERR_PRINT("Failed to create thread\n", NULL);
        return 1;
    }
    PRINT("SCANNING\n", NULL);
    pcap_dispatch(package_handle, 1, (pcap_handler) loop_back, (unsigned char *) &return_arg);

    if (timeout_args.running == 1) {
        pthread_cancel(thread_id);
        PRINT("CANCEL TREAD\n", NULL);
    }

    pcap_close(package_handle);
    if (net_dev_alloc) {
        free(network_device);
    } 
    
    return 0;
}