/*
 * UdpService.h
 *
 *  Created on: Dec 4, 2010
 *      Author: Gui
 */

#ifndef UDPSERVICE_H_
#define UDPSERVICE_H_

#include <stdio.h>
#include <signal.h>
#include "Poll.h"
#include <unistd.h>

void UdpAcceptCallback(int fd, short ev, void* arg);

#endif /* UDPSERVICE_H_ */
