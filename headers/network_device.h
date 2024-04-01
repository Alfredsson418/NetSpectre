struct network_device
{
    char name[100];
    char IPv4[INET_ADDRSTRLEN];
    char subnet_mask[INET_ADDRSTRLEN];
    char IPv6[INET6_ADDRSTRLEN];
};


struct network_device * get_first_network_dev(char errbuff[PCAP_ERRBUF_SIZE]);