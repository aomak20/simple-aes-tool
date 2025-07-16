// File:    aes_error.h
// Author:  Andrei Makarov
// Desc:    Header file, errors specifically for this program
// //

#ifndef AES_ERROR_HEADER
#define AES_ERROR_HEADER

typedef enum
{
    ERR_OK = 0,
    ERR_FILE_NOT_OPEN = -1,
    ERR_FILE_NOT_WRITE = -2,
    ERR_KEY_INVALID_LEN = -3
} AES_Error;

void aes_print_err(AES_Error err_code);

#endif
