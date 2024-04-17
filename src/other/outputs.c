#include "../../include/other/outputs.h"

void output(char * string, int output_to_terminal, int output_to_logile, char * log_file_location) {
    if (output_to_terminal) {
        printf("%s\n", string);
    }
    
}