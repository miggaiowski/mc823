/*
 * Services.c
 *
 *  Created on: Dec 4, 2010
 *      Author: Gui
 */

#include "Services.h"

void CreateAllSockets( struct ServiceArray* service_array )
{
  int i;
  for( i = 0; i < service_array->size; ++i )
    {
      struct Service* service = &(service_array->services[i]);

      service->hints.ai_family = AF_UNSPEC; // IPv6/IPv4
      service->hints.ai_flags = AI_PASSIVE; // Take my IP


      int error = getaddrinfo(	NULL,
				service->port,
				&(service->hints),
				&(service->res)
				);
      if( error )
	{
	  fprintf( stderr, "%s\n", gai_strerror( error ) );
	  exit(1);
	}

      if( ( service->socketfd =
	    socket(	service->res->ai_family,
			service->res->ai_socktype,
			service->res->ai_protocol ) ) == -1 )
	{
	  perror("socket");
	  exit(1);
	}

		int yes=1;
		if( setsockopt( service->socketfd,
						SOL_SOCKET,
						SO_REUSEADDR,
						&yes, sizeof(int) ) == -1 )
		{
			perror("setsockopt");
			exit(1);
		}

      if( ( bind( service->socketfd,
		  service->res->ai_addr,
		  service->res->ai_addrlen) ) == -1 )
	{
	  perror("bind");
	  exit(1);
	}

    }

}

// TODO: do we close sockets of running programs ?
void CloseAllSockets( struct ServiceArray* service_array )
{
  int i;
  for (i = 0; i < service_array->size; ++i)
    close( service_array->services[i].socketfd );

  free( service_array->services );
  free( service_array );
}
