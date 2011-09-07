/*
 * ParseServices.h
 *
 *  Created on: Dec 3, 2010
 *      Author: Gui
 */

#ifndef PARSESERVICES_H_
#define PARSESERVICES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "Services.h"

#define MAX_SERVICES 3
#define INET_CONF_PATH "./resources/myinetd.conf"

#define SOCKET_TYPE_BUFF_LEN 7
#define STREAM_STR "stream"
#define DGRAM_STR "dgram"

#define PROTOCOL_BUFF_LEN 4
#define UDP_STR "udp"
#define TCP_STR "tcp"

#define WAIT_BUFF_LEN 7
#define NOWAIT_STR "nowait"
#define WAIT_STR "wait"

#define ARG_BUFF_LEN 128

#define TAB '\t'
#define NEWLINE '\n'
#define SPACE_STR " "

struct ServiceArray* ParseServices(  );
void PrintServices( struct ServiceArray* service_array );

#endif /* PARSESERVICES_H_ */
