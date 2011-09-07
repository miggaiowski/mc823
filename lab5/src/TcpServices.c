/*
 * TcpServices.c
 */
#include "TcpServices.h"

static int is_tcp( struct Service* service );

void ListenAllTcp( struct ServiceArray* service_array )
{
	// for each service
	int i;
	for (i = 0; i < service_array->size; ++i)
	{
		struct Service* service = &( service_array->services[i] );

		if( is_tcp( service ) )
			listen( service->socketfd, BACKLOG );
	}

}

/**
 * Got a request from port accepting connection
 * @param int fd, socket
 */
void TcpAcceptCallback( int fd, short ev, void* arg )
{
	fprintf( stderr, "Tcp accept callback\n");

	struct sockaddr_storage their_addr;
	socklen_t their_addr_size;
	int client_fd =
			accept( fd, (struct sockaddr*) &their_addr, &their_addr_size );

	int pid;
	if( !(pid = fork() ) )
	{ // Child code inside

		/*  close all descriptors but client socket*/
		int i;
		for ( i = getdtablesize( ); i >= 0; --i )
			if( i != client_fd )
				close( i );

		// Duplicate socket for std in/out/err
		if( client_fd != STDIN_FILENO )
		{
			dup2( client_fd, STDIN_FILENO );
			close( client_fd );
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

	close( fd );
}

int is_tcp( struct Service* service )
{
	return service->protocol == TCP;
}

