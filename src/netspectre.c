#include "../headers/netspectre.h"
#include "../headers/network_device.h"
#include "../headers/packet_capture.h"

int main() {
    char errbuff[PCAP_ERRBUF_SIZE];
    struct network_device * device = get_first_network_dev(errbuff);
    pcap_t *handle;
    int packet_count_limit = 1;
    int timeout_limit = 10000;
    const unsigned char *packet;
    struct pcap_pkthdr packet_header;

    handle = pcap_open_live(device->name, BUFSIZ, packet_count_limit, timeout_limit, errbuff);

    if (handle == NULL) {
        printf("Could not open device %s: %s\n", device ->name, errbuff);
        return 2;
    }
    

    pcap_loop(handle, 0, packet_handler, NULL);
    pcap_close(handle);
    free(device);

}