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
    printf("Help message\n");
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
    char* input_path;
    char* output_path;
    char* key_path;
    char* iv_path;

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
        if(strcmp(argv[i], "-in") == 0)
        {
            if(i == argc - 1)
            {
                print_error("Expected more input");
                return 0;
            }
            input_path = argv[++i];
            printf("%s\n", input_path);
        }
        else if(strcmp(argv[i], "-out") == 0)
        {
            if(i == argc - 1)
            {
                print_error("Expected more input");
                return 0;
            }
            output_path = argv[++i];
            printf("%s\n", output_path);
        }
        else if(strcmp(argv[i], "-iv") == 0)
        {
            if(i == argc - 1)
            {
                print_error("Expected more input");
                return 0;
            }
            iv_path = argv[++i];
            printf("%s\n", iv_path);
        }
        else if(strcmp(argv[i], "-key") == 0)
        {
            if(i == argc - 1)
            {
                print_error("Expected more input");
                return 0;
            }
            key_path = argv[++i];
            printf("%s\n", key_path);
        }
        else if(strcmp(argv[i], "-e") == 0)
        {
            encrypt_flag = true;
            printf("encrypting\n");
        }
        else if(strcmp(argv[i], "-d") == 0)
        {
            decrypt_flag = true;
            printf("decrypting\n");
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

    return 0;
}
