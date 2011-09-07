/*
 * ParseServices.c
 *
 *  Created on: Dec 3, 2010
 *      Author: Gui
 */

#include "ParseServices.h"

static void ParseServiceName( FILE* fid, struct Service* service );
static void ParsePort( FILE* fid, struct Service* service );
static void ParseSocketType( FILE* fid, struct Service* service );
static void ParseProtocol( FILE* fid, struct Service* service );
static void ParseWait( FILE* fid, struct Service* service );
static void ParsePathname( FILE* fid, struct Service* service );
static void ParseArgs( FILE* fid, struct Service* service );
static void FillToTab( FILE* fid, char* array, int length );


/*
 * Read configuration FILE* to parse services
 */
struct ServiceArray* ParseServices(  )
{
	FILE* fid = fopen( INET_CONF_PATH, "r" );

	if( fid == NULL )
	{
		perror( "fopen" );
		exit( 1 );
	}

	struct ServiceArray* service_array = malloc( sizeof( struct ServiceArray ) );
	if( service_array == NULL )
	{
		perror( "malloc" );
		exit( 1 );
	}

	service_array->services = (struct Service*) malloc( MAX_SERVICES * sizeof(struct Service) );
	if( service_array->services == NULL )
	{
		perror( "malloc" );
		exit( 1 );
	}
	service_array->size = MAX_SERVICES;


	// For each services
	int i;
	for( i = 0; i < service_array->size; ++i )
	{
		struct Service* service = &( service_array->services[i] );
		service->pid = -1;
		service->accept_event = NULL;
		memset( &(service->hints), 0, sizeof(service->hints));
		ParseServiceName( fid, service );
		ParsePort( fid, service );
		ParseSocketType( fid, service );
		ParseProtocol( fid, service );
		ParseWait( fid, service );
		ParsePathname( fid, service );
		ParseArgs( fid, service );
	}

	return service_array;
}

/*
 * Print services
 * @params Services* service, an array of services
 */
void PrintServices( struct ServiceArray* service_array )
{
	int i;
	for (i = 0; i < service_array->size; ++i)
	{
		struct Service* service = &( service_array->services[i] );

		printf("%s ", service->name );

		printf( "%s ", service->port );

		if( service->hints.ai_socktype == SOCK_STREAM )
			printf( "stream ");
		else
			printf( "dgram " );


		if( service->protocol == UDP )
			printf( "udp" );
		else
			printf( "tcp" );

		if( service->wait == 0 )
			printf( "nowait " );
		else
			printf( "wait " );

		printf( "%s ", service->pathname );

		int j;
		for( j = 0; service->args[j]; ++j )
			printf( "(%d)%s ",j , service->args[j] );

		printf("\n");

	}
}

static void ParseServiceName( FILE* fid, struct Service* service )
{
	FillToTab( fid, service->name, SERVICE_LEN );
}

/*
 * Parse port number from FILE*
 * @param FILE* fid, FILE* to parse
 * @param struct Service* service to parse
 */
static void ParsePort( FILE* fid, struct Service* service )
{
	FillToTab( fid, service->port, PORT_LEN );
}

/*
 * Parse socket type stream/dgram from FILE*
 * @param FILE* fid, FILE* to parse
 * @param struct Service* service, service to parse
 */
static void ParseSocketType( FILE* fid, struct Service* service )
{
	char socket_type_buff[SOCKET_TYPE_BUFF_LEN];

	FillToTab( fid, socket_type_buff, SOCKET_TYPE_BUFF_LEN );

	if( strncmp( socket_type_buff, STREAM_STR,
			SOCKET_TYPE_BUFF_LEN ) == 0 )
	{
		service->hints.ai_socktype = SOCK_STREAM;
	}
	else if( strncmp( socket_type_buff, DGRAM_STR,
			SOCKET_TYPE_BUFF_LEN ) == 0 )
	{
		service->hints.ai_socktype = SOCK_DGRAM;
	}
	else
	{
		fprintf( stderr,"Unknown socket type:%s", socket_type_buff );
		fclose( fid );
		exit( 1 );
	}
}

/*
 * Parse protocol udp/tcp from FILE*
 * @param FILE* fid, FILE* to parse
 * @param struct Service* service, service to parse
 */
static void ParseProtocol( FILE* fid, struct Service* service )
{
	char protocol_buff[PROTOCOL_BUFF_LEN];

	FillToTab( fid, protocol_buff, PROTOCOL_BUFF_LEN );

	if( strncmp( protocol_buff, UDP_STR,
			PROTOCOL_BUFF_LEN ) == 0 )
	{
		service->protocol = UDP;
	}
	else if( strncmp( protocol_buff, TCP_STR,
			PROTOCOL_BUFF_LEN) == 0 )
	{
		service->protocol = TCP;
	}
	else
	{
		fprintf( stderr,"Unknown protocol: %s", protocol_buff );
		fclose( fid );
		exit( 1 );
	}
}

/*
 * Parse protocol wait/nowait from FILE*
 * @param FILE* fid, FILE* to parse
 * @param struct Service* service, service to parse
 */
static void ParseWait( FILE* fid, struct Service* service )
{
	char wait_buff[WAIT_BUFF_LEN];

	FillToTab( fid, wait_buff, WAIT_BUFF_LEN );

	if( strncmp( wait_buff, NOWAIT_STR, WAIT_BUFF_LEN ) == 0 )
	{
		service->wait = 0;
	}
	else if( strncmp( wait_buff, WAIT_STR, WAIT_BUFF_LEN ) == 0 )
	{
		service->wait = 1;
	}
	else
	{
		fprintf( stderr, "Unknown blocking: %s", wait_buff );
		fclose(fid);
		exit(1);
	}
}

/*
 * Parse Pathname for service application
 * @param FILE* fid, FILE* to parse
 * @param struct Service* service, service to parse
 */
static void ParsePathname( FILE* fid, struct Service* service )
{
	FillToTab( fid, service->pathname, PATH_LEN );
}

/*
 * Parse Args to call service application
 * @param FILE* fid, FILE* to parse
 * @param struct Service* service, service to parse
 */
static void ParseArgs( FILE* fid, struct Service* service )
{
	char* arg_buff = (char*) malloc( ARG_BUFF_LEN * sizeof(char) );
	FillToTab( fid, arg_buff, ARG_BUFF_LEN );

	int i = 0;
	char* token = strtok( arg_buff, SPACE_STR );
	while( token != NULL && i < MAX_ARG )
	{
		service->args[i] = token;
		token = strtok( NULL, SPACE_STR );
		i++;
	}
	service->args[i] = NULL;

}

/* Fill an array until is full or tab/eof is encounter
 *	@param FILE* fid, FILE* to read
 *	@param char* array, array to fill
 *	@param int len, length of the array
 */
static int BreakChar( char buff )
{
	return buff == TAB || buff == EOF || buff == NEWLINE;
}
static void FillToTab( FILE* fid, char* array, int length )
{
	int j;
	for (j = 0; j < length-1; ++j)
	{
		char buff = getc(fid);
		if ( BreakChar( buff )  )
			break;

		array[j] = buff;
	}

	if( j == length - 1 )
		while( !BreakChar( getc(fid) ) ){}

	array[j] = '\0';
}
