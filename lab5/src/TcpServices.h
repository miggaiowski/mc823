/*
 * TcpServices.h
 */

#ifndef TCPSERVICES_H_
#define TCPSERVICES_H_

#include "Services.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define BACKLOG 10
#define ROOT 0

void ListenAllTcp( struct ServiceArray* service_array );
void TcpAcceptCallback( int fd, short ev, void* arg );

#endif /* TCPSERVICES_H_ */
