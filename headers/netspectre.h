#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <string.h>

/*
    hexDump(addr, len, perLine);
        Usage:
        hexDump(addr, len, perLine);
            payload:    the address to start dumping from.
            len:     the number of bytes to dump.
            perLine: number of bytes on each output line.
        Return:
            Void
    Got from https://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data
    This function is also modified
*/
void hexdump (const unsigned char * payload, const int len, int perLine);