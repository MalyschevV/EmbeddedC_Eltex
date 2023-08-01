#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SIZE 128

int main() {
  int packets = 0;
  char buffer[SIZE];

  bzero(&buffer, SIZE);

  int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

  if (sock < 0) {
    perror("error create raw socket");
    exit(1);
  }

  struct sockaddr_in server;

  server.sin_family = AF_INET;
  server.sin_port = htons(7777);
  server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  while (1) {
    socklen_t lenght = sizeof(server);

    if (recvfrom(sock, buffer, SIZE, 0, (struct sockaddr*)&server, &lenght) <
        0) {
      perror("error recieve");
      exit(1);
    } else {
      packets++;
      printf("Current num of packets = %d\n", packets);
    }
  }
}