#include "../../include/other/replace.h"

// Function to replace all occurrences of a substring in a string
char * replace_substring(char *str, const char *old_sub, const char *new_sub) {
    char *result; // Pointer to store the modified string
    int i, count = 0; // Variables to count the occurrences of old_sub
    int new_sub_len = strlen(new_sub); // Length of new_sub
    int old_sub_len = strlen(old_sub); // Length of old_sub

    // Count the occurrences of old_sub in str
    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], old_sub) == &str[i]) {
            count++;
            i += old_sub_len - 1;
        }
    }

    // Allocate memory for the modified string
    result = (char *)malloc(i + count * (new_sub_len - old_sub_len) + 1);

    i = 0;
    // Replace old_sub with new_sub in str
    /*
        the while (*str) loop will continue executing the code inside it 
        as long as the value at the memory address pointed to by str is not '\0', 
        which indicates the end of the string.
    */
    while (*str) {
        // Check if the current position in str matches the start of old_sub
        if (strstr(str, old_sub) == str) {
            // If there is a match, copy new_sub to the result string
            strcpy(&result[i], new_sub);
            // Move the index i to the end of new_sub
            i += new_sub_len;
            // Move the pointer str to the end of old_sub
            str += old_sub_len;
        } else {
            // If there is no match, copy the current character from str to the result string
            result[i++] = *str++;
        }
    }

    result[i] = '\0'; // Add null terminator to the modified string
    return result; // Return the modified string
}

void replace_format(char **format, char *substring, char *replacement) {
    if (replacement == NULL) {
        DEBUG_MESSAGE("%s cant be replaced with NULL\n", substring);
        *format = replace_substring(*format, substring, "NULL");

    }else if (strstr(*format, substring) != NULL) {
        *format = replace_substring(*format, substring, replacement);
    } else {
        *format = replace_substring(*format, substring, "NULL");
    }
    
}
