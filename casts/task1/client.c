#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define SIZE 127
#define PORT 8888
#define GROUP "239.0.0.1"

int main() {
  char buffer[SIZE];
  struct sockaddr_in server;
  struct ip_mreq multicast;

  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0) {
    perror("error create socket");
    exit(1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  int serverlenght = sizeof(server);

  if (bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("error bind");
    exit(1);
  }

  multicast.imr_multiaddr.s_addr = inet_addr(GROUP);
  multicast.imr_interface.s_addr = htonl(INADDR_ANY);

  if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast,
                 sizeof(multicast)) < 0) {
    perror("setsockopt");
    exit(1);
  }

  while (1) {
    if (recvfrom(sock, buffer, SIZE, 0, (struct sockaddr*)&server,
                 &serverlenght) < 0) {
      perror("error recieve");
      exit(1);
    }

    printf("Received message from %s: %s\n", inet_ntoa(server.sin_addr),
           buffer);
  }
}