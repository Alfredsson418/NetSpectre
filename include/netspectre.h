#ifndef NETSPECTRE_H
#define NETSPECTRE_H

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdbool.h>
// https://www.gnu.org/software/libc/manual/html_node/Argp-Example-3.html
#include <argp.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>

#include "other/outputs.h"

#define IPV4_ADDR_STR_LEN 16 // 15 characters for the address and 1 for the null terminator

#endif