#include "../../include/netspectre.h"
#include "../../include/other/process_arguments.h"

// I want to pass arguments as a pointer, but is could not figure it out for the time beeing
void process_arguments(int argc, char *argv[], const int arguments_size, const struct argument_options arguments[]) {
    // printf("argc: %d all_size: %d\n", argc, arguments_size);

    // Ignore first two arguments
    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < arguments_size; j++) {
            // printf("%s : %s : %d \n", argv[i], allowed_arguments[j], strcmp(argv[i], allowed_arguments[j]));
            if (strcmp(argv[i], arguments[j].flag) != 0 || strcmp(argv[i], arguments[j].extended_flag) != 0) {
                printf("%s is not a valid argument for this process\n", argv[i]);
                exit(0);
            }
        }
    }

}


