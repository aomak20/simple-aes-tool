// File:    aes.c
// Author:  Andrei Makarov
// Desc:    The big AES file
// //

#include <errno.h>
#include <stdio.h>

#include "aes_error.h"
#include "aes_print.h"

int find_round_count(char *key_path)
{
    FILE *key_fp = fopen(key_path, "rb");
    if(key_fp == NULL)
    {
        if (errno == ENOENT)
        {
            aes_printf_error("Key file %s does not exist.\n", key_path);
        }
        else
        {
            aes_printf_error("Key file %s could not be opened.\n", key_path);
        }
        return ERR_FILE_NOT_OPEN;
    }

    fseek(key_fp, 0L, SEEK_END);
    long bytes_count = ftell(key_fp);
    fclose(key_fp);

    switch(bytes_count)
    {
        case 16L:
            return 10;
            break;
        case 24L:
            return 12;
            break;
        case 32L:
            return 14;
            break;
        default:
            aes_printf_error("Key file must be 16/24/32 bytes long, but is actually %d bytes.\n", bytes_count);
            return ERR_KEY_INVALID_LEN;
    }
}

int do_aes_ecb(char *input_path, char *output_path, char *key_path)
{
    aes_printf("Doing AES process in ECB mode with..\nInput: %s\nOutput: %s\nKey: %s\n", input_path, output_path, key_path);
    int round_count = find_round_count(key_path);
    if(round_count < 0)
    {
        return round_count;
    }
    aes_printf_verbose("Round count: %d\n", round_count);

    return ERR_OK;
}
