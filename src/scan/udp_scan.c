#include "../../include/scan/udp_scan.h"
/*
    As per my understanding, creating a UDP port scanner may take some time
    due to that it is hard to know if a port is open or not.
    The service may or may not responde, and you may or my not (dependent on OS)
    get an ICMP "Port unreachable" message in return.
*/
/*
    I could you the packet sniffer to find ICMP packages with the dst port
    number maching the searching port after a seach is created, then I can find
    out if the ICMP package is sent or not. In theory
*/

// Define a struct that holds the arguments for run_next_best_packet
typedef struct {
    struct pcap_pkthdr * packet_header;
    unsigned char * packet;
    char filter[60];
} next_best_args;

void * run_next_best_packet(void * arg) {
    next_best_args* args = (next_best_args*)arg;

    next_best_packet(&args->packet_header, &args->packet, "lo",args->filter, 1000);

    return;
}


int udp_scan(char ip[IPV4_ADDR_STR_LEN], int port) {

    pthread_t thread_id;

    // Create a struct that holds the arguments for run_next_best_packet
    next_best_args args;
    args.packet = calloc(MAX_PACKET_SIZE + 1, sizeof(char));
    // First is the udp dst port, second and this is too check if it is dst and por unrech
    sprintf(args.filter, "(icmp[30:2] == %#06x) && (icmp[0] == 3) && (icmp[1] == 3)", port);

    PRINT("%s\n", args.filter);
    if (pthread_create(&thread_id, NULL, run_next_best_packet, &args) != 0) {
        ERR_PRINT("Failed to create thread\n", NULL);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        ERR_PRINT("ERROR creating TCP socket!", NULL);
        return -1;
    }

    struct timeval timeout = {5, 0};  // 1 second timeout
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));


    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
        ERR_PRINT("Invalid address/ Address not supported \n", NULL);
        return -1;
    }
    sleep(1);
    if (sendto(sock, "hello", 6, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        ERR_PRINT("ERROR SENDING UDP PACKAGE\n", NULL);
        close(sock);
        return -1;
    }
    PRINT("Package Send!\n", NULL);

    pthread_join(thread_id, NULL);

    if (args.packet_header->len > 0) {
        PRINT("ICMP PACKET FOUND, PORT CLOSED\n", NULL);
    } else {
        PRINT("NO PACKET RECEIVED, PORT COULD BE OPEN\n", NULL);
    }
    /*
    socklen_t addr_size = sizeof(addr);
    int response = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addr_size);
    if (response < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            PRINT("Port %d is closed\n", port);
        } else {
            ERR_PRINT("ERROR RECEIVING UDP PACKAGE\n", NULL);
        }
        close(sock);
        return -1;
    }
    PRINT("Package Recevied!\n", NULL);
    buffer[response] = '\0';  // Null-terminate the string
    PRINT("%s\n", buffer);
    */

    close(sock);
    free(args.packet);
    return 0;
}