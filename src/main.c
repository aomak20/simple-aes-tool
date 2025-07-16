// File:    main.c
// Author:  Andrei Makarov
// Desc:    The main file
// //

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "aes.h"
#include "aes_error.h"

// Constants
const char *DECRYPT_POSTFIX = "-decrypted";
const char *ENCRYPT_POSTFIX = "-encrypted";
const int POSTFIX_LENGTH = strlen("-xxcrypted");

void print_help()
{
    printf("For detailed usage, use -h or --help\n");
}

void print_usage()
{
    printf("saes: Simple AES Utility (version 1.0)\n\n");

    printf("A simple AES program that runs in EBC mode. Write more stuff here later.\n\n");

    printf("\t-v, --version\t\t\tPrint version\n");
    printf("\t-h, --help\t\t\tPrint this help message\n");
    printf("\n");
    printf("\t-d, --decrypt\t\t\tDecryption mode\n");
    printf("\t-e, --encrypt\t\t\tEncryption mode\n");
    printf("\t-i, --input INPUT_FILE\t\tInput file path\n");
    printf("\t-o, --output OUTPUT_FILE\tOutput file path\n");
    printf("\t-k, --key KEY_FILE\t\tKey file path\n");
    printf("\n");
    printf("\t-f, --force\t\t\tForce output file overwrite\n");
    printf("\t-b, --verbose\t\t\tUse verbose message printing\n");
    printf("\t-q, --quiet\t\t\tSuppress messsage printing, overwrites --verbose\n");
    printf("\n");

    printf("Example usage:\n");
    printf("\tsaes [-d/-e] -i input_file [-o output_file] -k key_file [-f]\n");
}

void print_version()
{
    printf("Simple AES Utility version 1.0\n");
}

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        print_help();
        return ERR_OK;
    }

    // Flags and vars
    bool encrypt_flag = false;
    bool decrypt_flag = false;
    bool force_flag = false;
    bool verbose_flag = false;
    bool quiet_flag = false;
    char* input_path = NULL;
    char* output_path = NULL;
    char* key_path = NULL;

    int err_code = ERR_OK;

    // Preliminary check for help and version flags
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            print_usage();
            return err_code;
        }
        else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            print_version();
            return err_code;
        }
    }

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0)
        {
            if(i == argc - 1)
            {
                printf("Expected input file path.\n");
                return err_code;
            }
            input_path = argv[++i];
        }
        else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            if(i == argc - 1)
            {
                printf("Expected output file path.\n");
                return err_code;
            }
            output_path = argv[++i];
        }
        else if(strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--key") == 0)
        {
            if(i == argc - 1)
            {
                printf("Expected key file path.\n");
                return err_code;
            }
            key_path = argv[++i];
        }
        else if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--encrypt") == 0)
        {
            encrypt_flag = true;
        }
        else if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decrypt") == 0)
        {
            decrypt_flag = true;
        }
        else if(strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0)
        {
            force_flag = true;
        }
        else if(strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--verbose") == 0)
        {
            verbose_flag = true;
        }
        else if(strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0)
        {
            quiet_flag = true;
        }
        else{
            int err_msg_len = strlen("Unexpected flag \"") + strlen(argv[i]) + 2;
            char err_msg[err_msg_len];
            strcpy(err_msg, "Unexpected flag \"");
            strcat(err_msg, argv[i]);
            strcat(err_msg, "\".");
            printf("%s\n", err_msg);
            return err_code;
        }
    }

    // Special check to make sure --quiet overrides --verbose
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0)
        {
            quiet_flag = true;
            verbose_flag = false;
        }
    }

    // Validate flags/options
    if(encrypt_flag ^ decrypt_flag == 0)
    {
        printf("Must specify either encryption (-e) or decryption (-d), but not both.\n");
        return err_code;
    }
    if(input_path == NULL)
    {
        printf("Must specify input path (-i).\n");
        return err_code;
    }
    if(key_path == NULL)
    {
        printf("Must specify key path (-k).\n");
        return err_code;
    }
    if(output_path != NULL)
    {
        if(strcmp(input_path, output_path) == 0)
        {
            printf("Output file cannot be same as input file.\n");
            return err_code;
        }
        if(strcmp(key_path, output_path) == 0)
        {
            printf("Output file cannot be same as key file.\n");
            return err_code;
        }
    }

    // Allocate string for a possible newly constructed output_path
    int new_output_len = strlen(input_path) + POSTFIX_LENGTH;
    char new_output_path[new_output_len];

    if(output_path == NULL)
    {
        // Get the string of input before and after the .
        int extension_index;
        for(extension_index = 0; extension_index < strlen(input_path); extension_index++)
        {
            if(input_path[extension_index] == '.')
            {
                break;
            }
        }

        // Copy in input_path name portion
        strncpy(new_output_path, input_path, extension_index);
        // Copy in post-fix
        char output_postfix[POSTFIX_LENGTH + 1];    // + 1 to account for null terminator
        if(encrypt_flag)
        {
            strcpy(output_postfix, ENCRYPT_POSTFIX);
        }
        else{
            strcpy(output_postfix, DECRYPT_POSTFIX);
        }
        strcpy(&new_output_path[extension_index], output_postfix);
        // Copy in extension, if exists
        if(extension_index != strlen(input_path))
        {
            strcpy(&new_output_path[extension_index + POSTFIX_LENGTH], &input_path[extension_index]);
        }
        output_path = new_output_path;
    }

    // Debug prints
    //printf("input: %s\noutput: %s\nkey: %s\nencrypt: %d\ndecrypt: %d\n", input_path, output_path, key_path, encrypt_flag, decrypt_flag);
    //printf("force: %d\nquiet: %d\nverbose: %d\n", force_flag, quiet_flag, verbose_flag);

    // Validate existence of relevant files
    FILE *input_fp = fopen(input_path, "r");
    if(input_fp != NULL)
    {
        fclose(input_fp);
    }
    else{
        //printf("Input file %s does not exist.\n", input_path);
        err_code = ERR_FILE_NOT_OPEN;
        aes_print_err(err_code);
        return err_code;
    }

    FILE *key_fp = fopen(key_path, "r");
    if(key_fp != NULL)
    {
        fclose(key_fp);
    }
    else{
        //printf("Key file %s does not exist.\n", key_path);
        err_code = ERR_FILE_NOT_OPEN;
        aes_print_err(err_code);
        return err_code;
    }

    FILE *output_fp = fopen(output_path, "r");
    if(output_fp != NULL)
    {
        // File exists, check for overwrite
        if(!force_flag)
        {
            printf("Output file %s already exists. ", output_path);
            char overwrite_input[1];
            while(true)
            {
                printf("Overwrite? [y/n] ");
                scanf("%s", overwrite_input);
                if(strcmp(overwrite_input, "y") == 0)
                {
                    break;
                }
                else if(strcmp(overwrite_input, "n") == 0)
                {
                    printf("Exiting program...\n");
                    return err_code;
                }
                printf("Unrecognized input.\n");
            }
        }
    }
    output_fp = fopen(output_path, "w");
    if(output_fp == NULL)
    {
        //print_error("Could not overwrite output file.\n");
        err_code = ERR_FILE_NOT_OPEN;
        aes_print_err(err_code);
        return err_code;
    }
    fclose(output_fp);

    // By this point, confirmed that all relevant files are readable/writable
    
    err_code = do_aes_ecb(input_path, output_path, key_path);
    if(err_code != ERR_OK)
    {
        aes_print_err(err_code);
    }
    
    return err_code;
}
