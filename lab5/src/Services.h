/*
 * Services.h
 *
 *  Created on: Dec 4, 2010
 *      Author: Gui
 */

#ifndef SERVICES_H_
#define SERVICES_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <event.h>

#define SERVICE_LEN 32
#define PORT_LEN 6
#define PATH_LEN 256
#define MAX_ARG 20
#define ARG_LEN 32

typedef enum
{
	TCP,
	UDP
}Protocol;

struct Service
{
	char name[SERVICE_LEN];
	char port[PORT_LEN];
	Protocol protocol;
	int wait;
	char pathname[PATH_LEN];
	char* args[MAX_ARG+1];

	int socketfd;
	struct addrinfo hints;
	struct addrinfo* res;
	struct event* accept_event;

	int pid;
};



struct ServiceArray
{
	struct Service* services;
	int size;
};


void CreateAllSockets( struct ServiceArray* service_array );
void CloseAllSockets( struct ServiceArray* service_array );
#endif /* SERVICES_H_ */
