/*
 * UdpService.c
 *
 *  Created on: Dec 4, 2010
 *      Author: Gui
 */

#include "UdpServices.h"

void signal_handle( int sig )
{
	if( sig == SIGCHLD )
	{
		int pid = getpid();
		extern struct ServiceArray* service_array;

		int i;
		for( i = 0; i < service_array->size; ++i )
		{
			struct Service* service = &service_array->services[i];
			if( service->pid == pid )
			{
				PollAdd( service );
				service->pid = -1;
				return;
			}
		}
	}
}

void UdpAcceptCallback(int fd, short ev, void* arg)
{
	fprintf( stderr, "Udp accept callback\n");

	int pid = fork();

	signal( SIGCHLD, signal_handle );
	struct Service* service = (struct Service*) arg;
	service->pid = pid;
	PollRemove( service );

	if( !(pid) )
	{ // Child code inside

		/*  close all descriptors but client socket*/
		int i;
		for ( i = getdtablesize( ); i >= 0; --i )
			if( i != fd )
				close( i );

		// Duplicate socket for std in/out/err
		if( fd != STDIN_FILENO )
		{
			dup2( fd, STDIN_FILENO );
			close( fd );
		}
		dup2( STDIN_FILENO, STDOUT_FILENO );
		dup2( STDIN_FILENO, STDERR_FILENO );

		// We don't care about user/group

		// launch
		struct Service* service = (struct Service*) arg;
		if( ( execv( service->pathname, service->args ) ) == -1 )
		{
			perror("execv");
			exit(1);
		}
	}
}
