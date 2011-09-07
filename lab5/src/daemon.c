/*
 *
 *	UNIX Daemon Server Programming Sample Program
 *	Levent Karakas <levent at mektup dot at> May 2001
 *	Taken from: http://www.enderunix.org/documents/eng/daemon.php
 *  Created on: Nov 29, 2010
 *      Author: Levent Karakas
 *      Author: Guillaume MassŽ
 */

#include "daemon.h"

void log_message( char* message )
{
	FILE* logfile = fopen( LOG_FILE, "a");

	if( !logfile ) return;

	fprintf( logfile, "%s\n", message );

	fclose( logfile );
}

void log_message_ip( char* message, char* ip )
{
	FILE* logfile = fopen( LOG_FILE, "a");

	if( !logfile ) return;

	fprintf( logfile, "[%s]: %s\n", ip, message );

	fclose( logfile );
}

void log_message_stats( int lines, int chars )
{
	FILE* logfile = fopen( LOG_FILE, "a");

	if( !logfile ) return;

	fprintf( logfile, "Stats >> Lines: %d  Chars: %d\n", lines, chars );

	fclose( logfile );
}


void signal_handler( int sig )
{
	switch(sig)
	{

	case SIGHUP:
		log_message( "hangup signal caught" );
	break;

	case SIGTERM:
		log_message( "terminate signal caught" );
		exit(0);
	break;

	}
}


void create_daemon( int argc, char** argv )
{

	int i,lfp;
	char str[10];

	/* already a daemon */
	if( getppid() == 1 ) return;

	i = fork();
	if ( i < 0 ) exit( 1 ); // fork error
	if ( i > 0 ) exit( 0 ); // parent exits

	/* child (daemon) continues */

	/* obtain a new process group and be it's leader */
	setsid( );

	int method;
	if( argc == 2 )
		method = atoi(argv[1]);
	else
		method = 1;

	/* Avoid that deamon open a terminal device automaticly */
	if( method == 1 )
	{
		// refork
		i = fork();
		if ( i < 0 ) exit( 1 ); // fork error
		if ( i > 0 ) exit( 0 ); // parent exits
	}
	else if( method == 2 )
	{

		// Method 2
		/*  close all descriptors */
		for ( i = getdtablesize( ); i >= 0; --i )
			close( i );

		/*  handle standart I/O */
		i = open( "/dev/null", O_RDWR );
		dup( i );
		dup( i );
	}

	/* change running directory to one not mounted by the system */
	chdir( RUNNING_DIR );

	/* set newly created file permissions */
	umask( 027 );


	/* Create a lock file to make sute only one instance is running */
	lfp = open( LOCK_FILE, O_RDWR | O_CREAT, 0640 );
	if ( lfp < 0 ) exit( 1 ); // can not open
	if ( lockf( lfp, F_TLOCK, 0 ) < 0 ) exit( 0 ); // can not lock

	/* first instance continues */

	/* record pid to lockfile */
	sprintf( str, "%d\n", getpid( ) );
	write( lfp, str, strlen( str ) );

	/* ignore child */
	signal( SIGCHLD, SIG_IGN );

	/* ignore tty signals */
	signal( SIGTSTP, SIG_IGN );
	signal( SIGTTOU, SIG_IGN );
	signal( SIGTTIN, SIG_IGN );

	/* catch hangup signal */
	signal( SIGHUP, signal_handler );

	/* catch kill signal */
	signal( SIGTERM, signal_handler );
}



