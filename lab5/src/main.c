/*
 * main.c
 *
 *  Created on: Nov 29, 2010
 *      Author: Gui
 */

#include "daemon.h"
#include "Services.h"
#include "ParseServices.h"
#include "TcpServices.h"
#include "Poll.h"
#include <event.h>

struct ServiceArray* service_array;

int main( int argc, char** argv )
{
//	daemonize( argc, argv );

	service_array = ParseServices( );
	PrintServices(service_array);
	CreateAllSockets( service_array );

	ListenAllTcp( service_array );

	PollAddAll( service_array );

	PollLoop( );

	// 6. (TCP) create a child process to handle the connection
	//		close inetd socket for that connection
	// 6. (UDP) + save pid of child. disable with FD_CLR
	//			descriptor of this socket for future select
	//			set up SIGCHLD and go back to 4.
	//			When child die get child pid and enable
	//			select for this socket

	// 7. Child close all file descriptors except connection socket

	// 8. Child dup2 fd 0,1,2, close original open socket

	// 9. if service login is not root child call getpwnam to get input
	//		pass. call setgid and setuid to change group and user of service

	// 10. Child do exec to open program with pathname and args

	// 11. to get remote socket of client server, execed call getpeername
	//		with connected socket

	CloseAllSockets( service_array );

	return 0;
}
