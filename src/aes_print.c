// File:    aes_print.c
// Author:  Andrei Makarov
// Desc:    AES related print functions
// //

#include <stdarg.h>
#include <stdio.h>

#include "aes_print.h"
#include "aes_flags.h"

const char *AES_ERROR_PREFIX = "ERROR: ";

void aes_printf(const char *fmt, ...)
{
    if (aes_get_flags()->quiet)
    {
        return;
    }
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
}

void aes_printf_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "%s", AES_ERROR_PREFIX);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void aes_printf_verbose(const char *fmt, ...)
{
    if (aes_get_flags()->quiet || !(aes_get_flags()->verbose))
    {
        return;
    }
    va_list args;
    va_start(args, fmt);
    fprintf(stdout, "verbose: ");
    vfprintf(stdout, fmt, args);
    va_end(args);
}

