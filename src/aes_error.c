// File:    aes_error.c
// Author:  Andrei Makarov
// Desc:    Errors specifically for this program
// //

#include <stdio.h>

#include "aes_error.h"

void aes_print_err(AES_Error err_code)
{
    if(err_code == ERR_OK)
    {
        return;
    }

    printf("ERROR: ");
    switch(err_code)
    {
        case ERR_FILE_NOT_OPEN:
            printf("File could not be opened, or does not exist.\n");
            break;
        case ERR_FILE_NOT_WRITE:
            printf("Could not overwrite file.\n");
            break;
        case ERR_KEY_INVALID_LEN:
            printf("Key file must be 128/192/256 bits.\n");
            break;
    }
}
