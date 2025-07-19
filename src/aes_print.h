// File:    aes_print.h
// Author:  Andrei Makarov
// Desc:    Header for AES related print functions
// //

#ifndef AES_PRINT_HEADER
#define AES_PRINT_HEADER

extern const char *AES_ERROR_PREFIX;

void aes_printf(const char *fmt, ...);

void aes_printf_error(const char *fmt, ...);

void aes_printf_verbose(const char *fmt, ...);

#endif

