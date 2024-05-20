#ifndef REPLACE_H
#define REPLACE_H

#include "../netspectre.h"

/*
    char * replace_substring(char *str, const char *old_sub, const char *new_sub);
        Usage:
            str:    The string witch to process
            old_sub:     What to replace
            new_sub:    What to replace with
        Return:
            Formated string
*/
void replace_substring(char **str, const char *old_sub, const char *new_sub);

void replace_format(char **format, char *substring, char *replacement);

#endif