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

int main() {
  int sockfd, new_fd;  /* listen on sock_fd, new connection on new_fd */
  struct sockaddr_in my_addr;    /* my address information */
  struct sockaddr_in their_addr; /* connector's address information */
  int sin_size, nbytes;
  char buffer[BUFF_SIZE];    
  int numInLines = 0, totalInChars = 0;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  my_addr.sin_family = AF_INET;         /* host byte order */
  my_addr.sin_port = htons(MYPORT);     /* short, network byte order */
  my_addr.sin_addr.s_addr = INADDR_ANY; /* automatically fill with my IP */
  bzero(&(my_addr.sin_zero), 8);        /* zero the rest of the struct */

  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }
  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }

  while(1) {  /* main accept() loop */
    sin_size = sizeof(struct sockaddr_in);
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&sin_size)) == -1) {
      perror("accept");
      continue;
    }
    numInLines = 0; totalInChars = 0;
    fprintf(stderr, "Servidor: Conectado com %s\n",inet_ntoa(their_addr.sin_addr));

    char SendText[] = "Conectado, envie uma mensagem que eu devolvo.\n";
    if (send(new_fd, SendText, sizeof(SendText), 0) == -1){
      perror("send");
      exit(1);
    }
    while ( (nbytes = recv(new_fd, buffer, BUFF_SIZE, 0)) > 0 ) { // recebe msg do cliente
      numInLines++;
      totalInChars += nbytes;
      send(new_fd, buffer, nbytes, 0); // devolve a mesma coisa.
    }
    if (nbytes == 0) {
      fprintf(stderr, "Cliente fechou a conexão.\n");
      fprintf(stderr, "  Numero de linhas recebidas: %d\n", numInLines);
      fprintf(stderr, "  Total de caracteres recebidos: %d\n", totalInChars);
    }
    close(new_fd);  
  }
  return 0;
}


