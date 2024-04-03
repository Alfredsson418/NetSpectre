#include "netspectre.h"
#include "network_device.h"

void packet_handler(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet);

void print_packet_info(const unsigned char *packet, struct pcap_pkthdr packet_header);

char * determine_packet_protocol(uint16_t packet_protocol);

struct ethertype_protocol_mapping {
    uint16_t ether_type;
    char* protocol_name;
};

static const struct ethertype_protocol_mapping ethertype_protocol_map[] = {
    {0x0800, "IPv4"}, // Internet
    {0x0806, "ARP"}, // Address Resolution Protocol
    {0x0842, "Wake-on-lan"},
    {0x2000, "Cisco Discovery Protocol"},
    {0x22EA, "Stream Reservation Protocol"},
    {0x22F0, "AVTP"}, // Audio Video Transport Protocol
    {0x22F3, "IETF TRILL Protocol"},
    {0x6002, "DEC MOP RC"},
    {0x6003, "DECnet Phase IV, DNA Routing"},
    {0x6004, "DEC LAT"},
    {0x8035, "RARP"}, // Reverse Address Resolution Protocol
    {0x8100, "IEEE 802.1Q/IEEE 802.1aq"}, // VLAN-tagged frame (IEEE 802.1Q) and Shortest Path Bridging IEEE 802.1aq with NNI compatibility
    {0x8102, "SLPP"}, // Simple Loop Prevention Protocol
    {0x8103, "VLACP"}, // Virtual Link Aggregation Control Protocol
    {0x8137, "IPX"},
    {0x8204, "QNX Qnet"},
    {0x86dd, "IPv6"},
    {0x8808, "Ethernet flow control"},
    {0x8809, "Ethernet Slow Protocols e.g. LACP"},
    {0x8819, "CobraNet"},
    {0x8847, "MPLS unicast"},
    {0x8848, "MPLS multicast"},
    {0x8863, "PPPoE Discovery Stage"},
    {0x8864, "PPPoE Session Stage"},
    {0x887B, "HomePlug 1.0 MME"},
    {0x888E, "IEEE 802.1X"},// EAP over LAN
    {0x8892, "PROFINET"},
    {0x889A, "SCSI over Ethernet"}, // HyperSCSI
    {0x88A2, "AoE"}, // ATA over Ethernet
    {0x88A4, "EtherCAT"},
    {0x88A8, "IEEE 802.1ad"}, // Service VLAN tag identifier (S-Tag) on Q-in-Q tunnel
    {0x88AB, "Ethernet Powerlink"}, 
    {0x88B8, "GOOSE"}, // Generic Object Oriented Substation event
    {0x88B9, "GSE"}, // Generic Substation Events
    {0x88BA, "IEC 61850"}, // SV (Sampled Value Transmission)
    {0x88BF, "MikroTik RoMON"}, // Unofficial
    {0x88CC, "LLDP"}, // Link Layer Discovery Protocol
    {0x88CD, "SERCOS III"},
    {0x88E1, "HomePlug Green PHY"},
    {0x88E3, "IEC62439-2"}, // Media Redundancy Protocol
    {0x88E5, "IEEE 802.1AE"}, // MAC security (MACsec)
    {0x88E7, "IEEE 802.1ah"}, // Provider Backbone Bridges (PBB)
    {0x88F7, "PTP"}, // Precision Time Protocol (PTP) over IEEE 802.3 Ethernet 
    {0x88F8, "NC-SI"},
    {0x88FB, "PRP"}, // Parallel Redundancy Protocol
    {0x8902, "IEEE 802.1ag CFM / ITU-T Y.1731"}, // IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM) 
    {0x8906, "FCoE"}, // Fibre Channel over Ethernet
    {0x8914, "FCoE Initialization Protocol"},
    {0x8915, "RoCE"}, //RDMA over Converged Ethernet
    {0x891D, "TTE"}, // TTEthernet Protocol Control Frame
    {0x893a, "IEEE 1905.1"},
    {0x892F, "HSR"}, // High-availability Seamless Redundancy
    {0x9000, "Ethernet Configuration Testing Protocol"},
    {0xF1C1, "Redundancy Tag"} // Redundancy Tag (IEEE 802.1CB Frame Replication and Elimination for Reliability) 
};

int capture();