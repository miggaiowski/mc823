#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#define BACKLOG 10     /* how many pending connections queue will hold */
#define BUFF_SIZE 1000

/*function that writes the datetime in a buffer*/
int daytime(char * buf) {
   char *ctime();
   time_t time(), now;
   (void) time(&now);
   return sprintf(buf, "%s", ctime(&now));
}

int main(int argc, char *argv[]){

	int sockfd;  /* listen on sock_fd, new connection on new_fd */
	struct sockaddr_in my_addr;    /* my address information */
	struct sockaddr_in their_addr; /* connector's address information */
	socklen_t addr_len;
	int sin_size, nbytes;
	char buffer[BUFF_SIZE];

	sockfd = STDIN_FILENO;

	recvfrom( sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr *)&their_addr, &addr_len);
	nbytes = daytime(buffer);
	sendto(sockfd, buffer, nbytes, 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));

  /*gets socket info*/
  getpeername(sockfd,(struct sockaddr *)&their_addr, &addr_len);

  /*verifies if the connection is TCP or UDP*/
  if (strcmp( inet_ntoa(their_addr.sin_addr),"0.0.0.0") == 0)
  {
    /*udp*/ 



    close(sockfd);
  } 
  else
  {
    /*tcp*/

    /*write datetime*/
    nbytes = daytime(buffer);

    if (write(sockfd, buffer, nbytes) == -1)
      exit(1);

    close(sockfd);  
  }
  return 0;
}

