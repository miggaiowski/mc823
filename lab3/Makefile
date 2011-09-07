CC=gcc
#CC=/opt/local/bin/gcc-mp-4.6
CFLAGS=-Wall -O3

.PHONY: all clean

all: _client _server _c_client _c_server _flood _cpuwaster

_client: cludp_echo.c
	$(CC) $(CFLAGS) cludp_echo.c -o _client

_c_client: c_cludp_echo.c
	$(CC) $(CFLAGS) c_cludp_echo.c -o _c_client

_server: srvudp_echo.c
	$(CC) $(CFLAGS) srvudp_echo.c -o _server

_c_server: c_srvudp_echo.c
	$(CC) $(CFLAGS) c_srvudp_echo.c -o _c_server

_flood: flood.c
	$(CC) $(CFLAGS) flood.c -o _flood

_cpuwaster: cpuwaster.c
	$(CC) $(CFLAGS) cpuwaster.c -o _cpuwaster

clean:
	rm _*
