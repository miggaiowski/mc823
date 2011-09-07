/*
 * daemon.h
 *
 *  Created on: Nov 29, 2010
 *      Author: Gui
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define RUNNING_DIR	"/tmp"
#define LOCK_FILE	"EchoDaemon.lock"
#define LOG_FILE	"EchoDaemon.log"

void log_message( char* message );
void log_message_ip( char* message, char* ip );
void log_message_stats( int lines, int chars );
void signal_handler( int sig );
void daemonize( int method );


#endif /* DAEMON_H_ */
