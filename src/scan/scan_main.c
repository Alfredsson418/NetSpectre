#include "../../include/scan/scan_main.h"


int scan(int argc, char *argv[]) {
    // Varibles for argp
    struct scan_arguments *arguments = malloc(sizeof(struct scan_arguments));

    if (arguments == NULL) {
        ERR_PRINT("Failed to allocate memory for arguments\n", NULL);
        exit(0);
    }

    arguments->device = NULL;
    arguments->ports_format = NULL;
    arguments->scan_protocol = NULL;
    arguments->target = NULL;
    arguments->ports = NULL;
    arguments->timeout = 10;

    argp_parse(&scan_argp, argc, argv, 0, 0, arguments);
    DEBUG_MESSAGE("-------OUTPUT SETTINGS-------\n", NULL);
    DEBUG_MESSAGE("Debug is set to: %d\n", g_debug_enabled);
    DEBUG_MESSAGE("Verbose is set to: %d\n", g_verbose_enabled);
    DEBUG_MESSAGE("Output is set to: %d\n", g_no_terminal_output);
    DEBUG_MESSAGE("-------ARGUMENT SETTINGS-------\n", NULL);

    if (arguments->target == NULL) {
        ERR_PRINT("No target found!\n", NULL);
        exit(0);
    }

    if (arguments->device == NULL) {
        arguments->device = get_first_network_dev();
        if (arguments->device == NULL) {
            ERR_PRINT("Found no network device\n", NULL);
            exit(0);
        } else {
            DEBUG_MESSAGE("Device was not set, first found is %s\n", arguments->device);
        }
    }
    if (arguments->ports_format == NULL) {
        arguments->ports_format = "1-1000";
        DEBUG_MESSAGE("Port range was not set, using default %s\n", arguments->ports_format);
        
    }
    PRINT("Scanning on ports: %s\n", arguments->ports_format);
    arguments->ports_len = parse_ports(arguments->ports_format, &(arguments->ports));

    if (arguments->scan_protocol == NULL) {
        arguments->scan_protocol = "TCP";
        DEBUG_MESSAGE("Scanning protocol was given, using default %s\n", arguments->scan_protocol);
    }


    udp_scan("127.0.0.1", 631, 10);


    free(arguments->device);
    free(arguments->ports);
    free(arguments);
    return 0;


}