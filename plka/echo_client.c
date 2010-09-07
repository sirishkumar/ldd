#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>

int main() {
  /* Host and port number of the echo server */
  char* echo_host = "192.168.1.20";
  int echo_port = 7;
  int sockfd;
  struct sockaddr_in *server=
      (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
  
  /* Set address of server to be connected */
  server->sin_family = AF_INET;
  server->sin_port = htons(echo_port);      // Note network byte order!
  server->sin_addr.s_addr = inet_addr(echo_host);

  /* Create a socket (Internet address family, stream socket and 
     default protocol) */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  /* Connect to server */
  printf("Connecting to %s \n", echo_host);
  printf("Numeric: %u\n", server->sin_addr);
  connect(sockfd, (struct sockaddr*)server, sizeof(*server));

  /* Send message */
  char* msg = "Hello World";
  printf("\nSend: '%s'\n", msg);
  write(sockfd, msg, strlen(msg));

  /* ... and receive result */
  char* buf = (char*)malloc(1000); // Receive buffer for max. 1000 chars
  int bytes = read(sockfd, (void*)buf, 1000);
  printf("\nBytes received: %u\n", bytes);
  printf("Text: '%s'\n", buf);
                   
  /* End communication (i.e. close socket) */
  close(sockfd);
}
