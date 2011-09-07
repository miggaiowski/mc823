/*
 * Poll.c
 *
 *  Created on: Dec 4, 2010
 *      Author: Gui
 */

#include "Poll.h"

static int service_not_set( struct Service* service );
static void set_service( struct Service* service );

void PollAddAll( struct ServiceArray* service_array )
{

  event_init();

  int i;
  for (i = 0; i < service_array->size; ++i)
    {
      struct Service* service = &( service_array->services[i] );
      PollAdd( service );
    }
}

void PollAdd( struct Service* service )
{
	if( service_not_set( service ) )
		set_service(service);

	event_add( service->accept_event, NULL);
}

void PollRemove( struct Service* service )
{
  event_del( service->accept_event );
}

void PollLoop( )
{
  event_dispatch();
}

void set_service( struct Service* service )
{
  service->accept_event = (struct event*) malloc( sizeof(struct event));
  if( service->accept_event == NULL )
    {
      perror("malloc");
      exit(1);
    }

	if( service->protocol == UDP )
	{
		event_set(	service->accept_event,
						service->socketfd,
						EV_READ,
						UdpAcceptCallback,
						service );
	}
	else if( service->protocol == TCP )
	{
		event_set(	service->accept_event,
						service->socketfd,
						EV_READ,
						TcpAcceptCallback,
						service );
	}
	else
	{
		fprintf( stderr, "Unknown protocol %d\n", (int) service->protocol );
		exit(1);
	}
}

int service_not_set( struct Service* service )
{
  return service->accept_event == NULL;
}
