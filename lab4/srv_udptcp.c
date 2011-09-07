/*
** srv_udptcp.c -- um exemplo de servidor interativo TCP e UDP usando select
Celio G.				
*/

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

#define MYPORT 3490    /* the port users will be connecting to */

#define BACKLOG 10     /* how many pending connections queue will hold */
#define MAXBUFLEN 128

#define max(x,y) ((x) > (y) ? (x) : (y) )

int udptcpsocket(int myport, char * protocol) {
    int sockfd, type;
    struct sockaddr_in my_addr;    /* my address information */
    if (strcmp(protocol, "tcp") ==0) 
	type = SOCK_STREAM;
    else 
	type = SOCK_DGRAM;
    if ((sockfd = socket(AF_INET, type, 0)) == -1) {
	perror("socket");
	exit(1);
    }

    my_addr.sin_family = AF_INET;         /* host byte order */
    my_addr.sin_port = htons(myport);     /* short, network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* automatically fill with my IP */
    bzero(&(my_addr.sin_zero), 8);        /* zero the rest of the struct */

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
	perror("bind");
	exit(1);
    }
    if (type == SOCK_STREAM)
	if (listen(sockfd, BACKLOG) == -1) {
	    perror("listen");
	    exit(1);
	} /* else  printf("Listening socket is %d\n", sockfd); */
    return sockfd;
}

void daytime(char * buf) {
    char *ctime();
    time_t time(), now;
    (void) time(&now);
    sprintf(buf, "%s", ctime(&now));
}

void main() {
    fd_set readfds;
    int tsockfd,usockfd,  new_fd;  /* listen on sock_fd, new connection on new_fd */
    int nfds, sin_size, numbytes;
    char buf[MAXBUFLEN];
    struct sockaddr_in their_addr; /* connector's address information */
    tsockfd= udptcpsocket(MYPORT, "tcp");
    usockfd= udptcpsocket(MYPORT, "udp");
    nfds = max(tsockfd, usockfd) +1;
    /* printf("tcp socket descriptor = %d udp socket descriptor= %d\n", tsockfd, usockfd);*/
    FD_ZERO(&readfds);
    sin_size = sizeof(struct sockaddr_in);

    while(1) {  /* main accept() loop */
	FD_SET(tsockfd, &readfds);
	FD_SET(usockfd, &readfds);

	if (select( nfds, &readfds, NULL, NULL, NULL) < 0){
	    perror("select" );
	    exit(1);
	}
	if (FD_ISSET(tsockfd, &readfds)) { 	/* We have a TCP connection */

	    if ((new_fd = accept(tsockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
		perror("accept");
		exit(1);
	    }
	    printf("server: got tcp connection from %s\n",inet_ntoa(their_addr.sin_addr));
	    daytime(buf);
	    if (write(new_fd, buf, strlen(buf)) == -1){
		perror("send");
		exit(1);
	    }
	    printf("sent: %s", buf);
	    close(new_fd);  

	}
	if (FD_ISSET(usockfd, &readfds)){ 		/* We have a UDP request */
	    if ((numbytes=recvfrom(usockfd,buf,MAXBUFLEN,0,(struct sockaddr *)&their_addr,                         &sin_size)) == -1) {
		perror("recvfrom");
		exit(1);
	    }
	    daytime(buf);
	    if ((numbytes=sendto(usockfd,buf,strlen(buf),0,(struct sockaddr *)&their_addr,                         sizeof(struct sockaddr))) == -1) {
		perror("sendto");
		exit(1);
	    }
	    printf("server: got udp request from: %s sent: %s",inet_ntoa(their_addr.sin_addr), buf);
	}
    } /* while */ 
}
