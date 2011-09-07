CC=gcc
#CC=/opt/local/bin/gcc-mp-4.6
CFLAGS=-Wall -O3

.PHONY: all clean

all: client server_echo

client: client0.c
	$(CC) $(CFLAGS) client0.c -o _client

server_echo: server_echo.c
	$(CC) $(CFLAGS) server_echo.c -o _server_echo

clear: clean

clean:
	rm -r _*
