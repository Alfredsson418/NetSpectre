#include "network_device.h"

struct network_device * get_first_network_dev(char errbuff[PCAP_ERRBUF_SIZE]) {
    pcap_if_t *all_devices = NULL;
    struct network_device * network_device = malloc(sizeof(struct network_device));

    if (pcap_findalldevs(&all_devices, errbuff) == -1) {
        // handle error
        return NULL;
    }
    
    if (all_devices == NULL) {
        strcpy(errbuff, "No devices found");
        return NULL;
    }

    if (all_devices->name == NULL) {
        strcpy(network_device->name, "None");
    } else {
        strcpy(network_device->name, all_devices->name);
    }


    struct pcap_addr *a;
    for (a = all_devices->addresses; a != NULL; a = a->next) {
                          
        if (a->addr != NULL && a->addr->sa_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)a->addr;
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(ipv4->sin_addr), ip, INET_ADDRSTRLEN);
            strcpy(network_device->IPv4, ip);

        } 
        if (a->addr != NULL && a->addr->sa_family == AF_INET6) {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)a->addr;
            char ip[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, &(ipv6->sin6_addr), ip, INET6_ADDRSTRLEN);
            strcpy(network_device->IPv6, ip);
        }
        if (a->netmask != NULL && a->netmask->sa_family == AF_INET) {
            struct sockaddr_in *subnet = (struct sockaddr_in *)a->netmask;
            char subnet_mask[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(subnet->sin_addr), subnet_mask, INET_ADDRSTRLEN);
            strcpy(network_device->subnet_mask, subnet_mask);
        }
            
    }

    pcap_freealldevs(all_devices);

    return network_device;


    // for(d= devices; d != NULL; d= d->next) {
        /*
        bpf_u_int32 ip_raw; // IP address as integer
        bpf_u_int32 subnet_mask_raw; // Subnet mask as integer
        int lookup_return_code;
        char ip[13];
        char subnet_mask[13];
        struct in_addr address; // Used for both ip & subnet
        */

        /*  Alternative way to get info about device
        printf("%d. %s\n", ++i, d->name);


        lookup_return_code = pcap_lookupnet(d->name, &ip_raw, &subnet_mask_raw, errbuff);
        if (lookup_return_code == -1) {
            printf("%s\n", errbuff);
            return 1;
        }

        // Get ip in human readable form
        address.s_addr = ip_raw;
        strcpy(ip, inet_ntoa(address));
        if (ip == NULL) {
            perror("inet_ntoa"); // print error
            return 1;
        }

        // Get subnet mask in human readable form
        address.s_addr = subnet_mask_raw;
        strcpy(subnet_mask, inet_ntoa(address));
        if (subnet_mask == NULL) {
            perror("inet_ntoa");
            return 1;
        }

        printf("IP address: %s\n", ip);
        printf("Subnet mask: %s\n", subnet_mask);
        */
    // }
}

/*
int main() {
    char err[PCAP_ERRBUF_SIZE];
    struct network_device *device = get_first_network_dev(err);
    if (device == NULL) {
        printf("%s", err);
    }
    printf("%s",device->name);
    free(device);
    
}
*/