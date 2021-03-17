// error.c
// Řešení IJC-DU1, příklad b), 17.3.2021
// Autor: Viktor Kubec, FIT
// Přeloženo: gcc 9.3.0

#include "error.h"

void warning_msg(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr,"CHYBA: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr,"CHYBA: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}
