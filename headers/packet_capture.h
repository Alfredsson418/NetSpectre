// Callback function used for pcap_loop that handles packages
void packet_handler(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet);

void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header);
