CC=gcc
#EVENT_DIR=/opt/local
#EVENT_DIR=/usagers/gumasa/MC823/libevent
EVENT_DIR=/home/specg10-2/ra107888/libevent
CFLAGS= -c -Wall -I$(EVENT_DIR)/include -g
LDFLAGS= $(EVENT_DIR)/lib/libevent.a -lrt

EXEC_INETD=_myinetd_
EXEC_DATETIME=_datetime_
EXEC_SERVER_ECHO=_server_echo_

all: myinetd datetime server_echo

server_echo: server_echo.c
	$(CC) server_echo.c -o ../$(EXEC_SERVER_ECHO)

datetime: datetime.c
	$(CC) datetime.c -o ../$(EXEC_DATETIME) 

myinetd: main.o daemon.o ParseServices.o Services.o TcpServices.o Poll.o
	$(CC) main.o daemon.o ParseServices.o Services.o UdpServices.o TcpServices.o Poll.o -o ../$(EXEC_INETD) $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

daemon.o: daemon.c daemon.h
	$(CC) $(CFLAGS) daemon.c
	
ParseServices.o: ParseServices.c ParseServices.h Services.o
	$(CC) $(CFLAGS) ParseServices.c

Poll.o: Poll.c Poll.h TcpServices.o UdpServices.o Services.o
	$(CC) $(CFLAGS) Poll.c
	
TcpServices.o: TcpServices.c TcpServices.h Services.o
	$(CC) $(CFLAGS) TcpServices.c

UdpServices.o: UdpServices.c UdpServices.h Services.o
	$(CC) $(CFLAGS) UdpServices.c

Services.o: Services.c Services.h
	$(CC) $(CFLAGS) Services.c

clean:
	rm *.o
	rm ../_*_
