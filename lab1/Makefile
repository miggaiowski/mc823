CC=gcc
#CC=/opt/local/bin/gcc-mp-4.6
CFLAGS=-Wall

.PHONY: all clean

all: client server_echo serverb

client: client0.c
	$(CC) $(CFLAGS) client0.c -o client

serverb: serverb.c
	$(CC) $(CFLAGS) serverb.c -o serverb

server_echo: server_echo.c
	$(CC) $(CFLAGS) server_echo.c -o server_echo

clear: clean

clean:
	@if test -e client; then	\
		rm client;				\
		echo rm client;			\
	fi 				

	@if test -e serverb; then	\
		rm serverb;				\
		echo rm serverb;		\
	fi

	@if test -e server_echo; then	\
		rm server_echo;				\
		echo rm server_echo;		\
	fi
