#include "../../include/netspectre.h"
#include "../../include/other/process_arguments.h"

// I want to pass arguments as a pointer, but is could not figure it out for the time beeing
void process_arguments(int argc, char *argv[], const int allowed_arguments_size, const struct argument_options allowed_arguments[], char * arguments[]) {
    // printf("argc: %d all_size: %d\n", argc, arguments_size);

    // Ignore first two arguments
    for (int i = 2; i < argc; i++) {
        if (is_flag(argv[i])) {
            bool found = false;
            for (int j = 0; j < allowed_arguments_size; j++) {
                // Checks if the given value is a valid flag
                if (strcmp(argv[i], allowed_arguments[j].flag) == 0 || strcmp(argv[i], allowed_arguments[j].extended_flag) == 0) {
                    found = true;
                    // Checks if you need more data
                    if (allowed_arguments[j].needs_value) {
                        // If the flag is at the end and there is no possible value
                        if (i + 1 >= argc) {
                            printf("No value for %s\n", argv[i]);
                            exit(0);
                        }
                        strcpy(arguments[j], argv[i + 1]);
                        i++;
                    }
                }
            }
            if (!found) {
                printf("%s is not a valid argument\n", argv[i]);
                exit(0);
            }
        } else { // If there is some random value
            printf("Undefined value: %s\n", argv[i]);
            exit(0);
        }
        /*
        if (is_flag(argv[i])) {
            bool found = false;
            for (int j = 0; j < arguments_size; j++) {
                if (strcmp(argv[i], arguments[j].flag) == 0 || strcmp(argv[i], arguments[j].extended_flag) == 0) {
                    found = true;
                    if (arguments[j].needs_value) {
                        if (i + 1 >= argc) {
                            printf("No value for %s\n", argv[i]);
                            exit(0);
                        }
                    }
                }
            }
            if (!found) {
                printf("%s is not a valid argument\n", argv[i]);
                exit(0);
            }
        }
        */
    }
}


bool is_flag(char * string) {
    int string_size = strlen(string);

    // Short flag e.g -f
    if (string_size == 2) {
        if (string[0] == '-') { return true; }
    } else if (string_size > 2) {
        if (string[0] == '-' && string[1] == '-') { return true; }
    }

    return false;
    
}


