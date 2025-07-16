// File:    aes_error.c
// Author:  Andrei Makarov
// Desc:    Errors specifically for this program
// //

#include <stdio.h>
#include <stdarg.h>

#include "aes_error.h"

const char *AES_ERROR_PREFIX = "ERROR: ";

void aes_perror(AES_Error err_code)
{
    if(err_code == ERR_OK)
    {
        return;
    }

    fprintf(stderr, "ERROR: ");
    switch(err_code)
    {
        case ERR_FILE_NOT_OPEN:
            fprintf(stderr, "File could not be opened, or does not exist.\n");
            break;
        case ERR_FILE_NOT_WRITE:
            fprintf(stderr, "Could not overwrite file.\n");
            break;
        case ERR_KEY_INVALID_LEN:
            fprintf(stderr, "Key file must be 128/192/256 bits.\n");
            break;
    }
}

void aes_pferror(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "%s", AES_ERROR_PREFIX);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}
