// File:    aes.c
// Author:  Andrei Makarov
// Desc:    The big AES file
// //

#include <stdio.h>

int find_round_count(char *key_path)
{
    FILE *key_fp = fopen(key_path, "rb");
    if(key_fp == NULL)
    {
        //TODO replace this with print_error call, involves moving print_error to a util.h file
        printf("ERROR could not open file\n");
        return -2;
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
            return -1;
    }
}

void do_aes_ecb(char *input_path, char *output_path, char *key_path)
{
    printf("Doing AES process in ECB mode with..\nInput: %s\nOutput: %s\nKey: %s\n", input_path, output_path, key_path);
    int round_count = find_round_count(key_path);
    //TODO remember how to do better error handling in C
    switch(round_count)
    {
        case -1:
            //TODO replace this with print_error call, involves moving print_error to a util.h file
            printf("ERROR key length must be 128/192/256 bits\n");
            break;
        case -2:
            break;
    }
    printf("Round count: %d\n", round_count);
}
