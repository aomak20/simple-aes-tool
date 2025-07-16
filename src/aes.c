// File:    aes.c
// Author:  Andrei Makarov
// Desc:    The big AES file
// //

#include <stdio.h>

#include "aes_error.h"

int find_round_count(char *key_path)
{
    FILE *key_fp = fopen(key_path, "rb");
    if(key_fp == NULL)
    {
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
            return ERR_KEY_INVALID_LEN;
    }
}

int do_aes_ecb(char *input_path, char *output_path, char *key_path)
{
    printf("Doing AES process in ECB mode with..\nInput: %s\nOutput: %s\nKey: %s\n", input_path, output_path, key_path);
    int round_count = find_round_count(key_path);
    if(round_count < 0)
    {
        return round_count;
    }
    printf("Round count: %d\n", round_count);

    return 0;
}
