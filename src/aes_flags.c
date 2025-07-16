// File:    aes_flags.c
// Author:  Andrei Makarov
// Desc:    Global storage for program flags
// //

#include <stdbool.h>

#include "aes_flags.h"

AESFlags *aes_get_flags()
{
    static AESFlags flags = {
        .encrypt = false,
        .decrypt = false,
        .verbose = false,
        .quiet = false,
        .force = false
    };

    return &flags;
}
