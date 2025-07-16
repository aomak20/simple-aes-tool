CC = gcc

CFLAGS = -std=c99 -Wall -Wextra -I./src

SRC = src/main.c src/aes.c src/aes_error.c

OUT = out/saes.exe

$(OUT):
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
