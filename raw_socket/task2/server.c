#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 100
#define SLLEP_TIME 2

int main() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0) {
    perror("socket create");
    exit(1);
  }

  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(7777);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  printf("Server: port - %d\n", ntohs(addr.sin_port));
  printf("Server: IP - %s\n", inet_ntoa(addr.sin_addr));

  struct sockaddr_in client_addr;
  int message;
  char buffer[SIZE];
  socklen_t lenght;

  lenght = sizeof(client_addr);
  bzero(&buffer, SIZE);

  message = recvfrom(sock, &buffer, SIZE, 0, (struct sockaddr *)&client_addr,
                     &lenght);
  if (message < 0) {
    perror("error recieve message");
    exit(1);
  }

  printf("SERVER: message from client: %s\n", buffer);

  buffer[0] = 'N';

  sleep(SLLEP_TIME);

  if (sendto(sock, buffer, SIZE, 0, (struct sockaddr *)&client_addr,
             sizeof(client_addr)) < 0) {
    perror("cannot send message to client");
    exit(1);
  }

  close(sock);
}