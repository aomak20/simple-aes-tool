// File:    aes_flags.h
// Author:  Andrei Makarov
// Desc:    Header file, global storage for program flags
// //

#ifndef AES_FLAGS_HEADER
#define AES_FLAGS_HEADER

#include <stdbool.h>

typedef struct {
    bool encrypt, decrypt, verbose, quiet, force;
} AESFlags;

AESFlags *aes_get_flags();

#endif
