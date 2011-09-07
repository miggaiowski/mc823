/* server_echo.c - Servidor simples */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MYPORT 9001    /* the port users will be connecting to */
#define BACKLOG 10     /* how many pending connections queue will hold */
#define BUFF_SIZE 1000

int main()
{
	int sockfd;  /* listen on sock_fd, new connection on new_fd */
	struct sockaddr_in my_addr;    /* my address information */
	struct sockaddr_in their_addr; /* connector's address information */
	socklen_t addr_len;
	int sin_size, nbytes;
	char buffer[BUFF_SIZE];

	sockfd = STDIN_FILENO;

	while ( (nbytes = recvfrom( sockfd,
								buffer,
								BUFF_SIZE, 0,
								(struct sockaddr *)&their_addr,
								&addr_len)) > 0 )
	{
	  sendto(sockfd, buffer, nbytes, 0, (struct sockaddr *)&their_addr,sizeof(struct sockaddr)); // devolve a mesma coisa.
	}

	close(sockfd);

  return 0;
}
