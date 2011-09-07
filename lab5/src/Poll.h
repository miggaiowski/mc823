/*
 * Poll.h
 *
 *  Created on: Dec 4, 2010
 *      Author: Gui
 */

#ifndef POLL_H_
#define POLL_H_

#include "Services.h"
#include "TcpServices.h"
#include "UdpServices.h"

/**
 * Add all services to the poll
 * @param Service* services, an array of services
 * @param int size, the size of the array
 */
void PollAddAll( struct ServiceArray* service_array );

/**
 * Add one service to the poll
 * @param Service* service, a service
 */
void PollAdd( struct Service* service );

/**
 * Remove one service from the poll
 * @param Service* service, a service
 */
void PollRemove( struct Service* service );

/**
 * Wait for an event to occur
 */
void PollLoop( );

#endif /* POLL_H_ */
