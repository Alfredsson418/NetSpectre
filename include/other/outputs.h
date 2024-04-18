#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "../netspectre.h"

extern int g_verboseEnabled;
extern int g_debugEnabled;

#define VERBOSE_MESSAGE(fmt, ...)\
do{\
    if(g_verboseEnabled) fprintf(stdout, fmt, __VA_ARGS__);\
}while(0)

#define DEBUG_MESSAGE(fmt, ...)\
do{\
    if(g_debugEnabled) {\
        fprintf(stdout, "DEBUG: ");\
        fprintf(stdout, fmt, __VA_ARGS__);\
    } \
}while(0)

#define PRINT(fmt, ...)\
do{\
    fprintf(stdout, fmt, __VA_ARGS__);\
}while(0)

#define ERR_PRINT(fmt, ...)\
do{\
    fprintf(stderr, "ERR: ");\
    fprintf(stderr, fmt, __VA_ARGS__);\
}while(0)

#endif