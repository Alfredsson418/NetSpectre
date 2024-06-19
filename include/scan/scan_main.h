#ifndef SCAN_MAIN_H
#define SCAN_MAIN_H

#include "../netspectre.h"
#include "scan_arguments.h"
#include "tcp_scan.h"
#include "udp_scan.h"

/*
    Parameters:
        argc: Program start argument length.
        argv: The array of start arguments.
    Return:
        If run
*/
int scan(int argc, char *argv[]);

#endif