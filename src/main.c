// File:    main.c
// Author:  Andrei Makarov
// Desc:    The main file
// //

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void print_help()
{
    printf("For detailed usage, use -h or --help\n");
}

void print_error(char err_msg[])
{
    printf("ERROR: %s\n", err_msg);
    print_help();
}

void print_usage()
{
    printf("saesu: Simple AES Utility\n\n");

    printf("A simple AES program that runs in EBC mode. Write more stuff here later.\n\n");

    printf("-d, --decrypt\tDecryption mode\n");
    printf("-e, --encrypt\tEncryption mode\n");
    printf("-f, --force\tForce output file overwrite\n");
    printf("-i, --input\tInput file path\n");
    printf("-o, --output\tOutput file path\n");
    printf("-k, --key\tKey file path\n\n");

    printf("Example usage:\n");
    printf("saesu [-d/-e] -i input_file [-o output_file] -k key_file [-f]\n");
}

void print_version()
{
    printf("Version message\n");
}

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        print_help();
        return 0;
    }

    // Flags and vars
    bool encrypt_flag = false;
    bool decrypt_flag = false;
    bool force_flag = false;
    char* input_path = NULL;
    char* output_path = NULL;
    char* key_path = NULL;

    // Preliminary check for help and version flags
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            print_usage();
            return 0;
        }
        else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
        {
            print_version();
            return 0;
        }
    }

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0)
        {
            if(i == argc - 1)
            {
                print_error("Expected input file path");
                return 0;
            }
            input_path = argv[++i];
        }
        else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            if(i == argc - 1)
            {
                print_error("Expected output file path");
                return 0;
            }
            output_path = argv[++i];
        }
        else if(strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--key") == 0)
        {
            if(i == argc - 1)
            {
                print_error("Expected key file path");
                return 0;
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
        else{
            int err_msg_len = strlen("Unexpected flag \"") + strlen(argv[i]) + 1;
            char err_msg[err_msg_len];
            strcpy(err_msg, "Unexpected flag \"");
            strcat(err_msg, argv[i]);
            strcat(err_msg, "\"");
            print_error(err_msg);
            return 0;
        }
    }

    // Validate flags/options
    if(encrypt_flag ^ decrypt_flag == 0)
    {
        print_error("Must specify either encryption (-e) or decryption (-d), but not both.\n");
        return 0;
    }
    if(input_path == NULL)
    {
        print_error("Must specify input path (-i).\n");
        return 0;
    }
    if(key_path == NULL)
    {
        print_error("Must specify key path (-k).\n");
        return 0;
    }
    if(output_path != NULL)
    {
        if(strcmp(input_path, output_path) == 0)
        {
            print_error("Output file cannot be same as input file.\n");
            return 0;
        }
        if(strcmp(key_path, output_path) == 0)
        {
            print_error("Output file cannot be same as key file.\n");
            return 0;
        }
    }

    // Allocate string for a possible newly constructed output_path
    int new_output_len = strlen(input_path) + strlen("-xxcrypted");

    char* input_name;
    char* input_ext;
    input_name = strtok(input_path, ".");
    input_ext = strtok(NULL, "");

    char new_output_path[new_output_len];

    if(output_path == NULL)
    {
        strcpy(new_output_path, input_name);
        if(encrypt_flag)
        {
            strcat(new_output_path, "-encrypted");
        }
        else{
            strcat(new_output_path, "-decrypted");
        }
        if(input_ext != NULL)
        {
            strcat(new_output_path, ".");
            strcat(new_output_path, input_ext);
        }

        output_path = new_output_path;
    }

    // Debug prints
    printf("input: %s\noutput: %s\nkey: %s\nencrypt: %d\ndecrypt: %d\n", input_path, output_path, key_path, encrypt_flag, decrypt_flag);

    return 0;
}
