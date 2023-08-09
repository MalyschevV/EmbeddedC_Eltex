#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 64

int main() {
  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sock < 0) {
    perror("error create socket");
    exit(1);
  }

  char packet[SIZE];

  memset(&packet, 0, SIZE);

  struct sockaddr_in client;
  struct sockaddr_in server;

  server.sin_family = AF_INET;
  server.sin_port = htons(7777);
  server.sin_addr.s_addr = INADDR_ANY;

  socklen_t lenght = sizeof(struct sockaddr_in);

  if (bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) {
    perror("error bind socket");
    exit(1);
  }

  printf("Server: port - %d\n", ntohs(server.sin_port));
  printf("Server: IP - %s\n", inet_ntoa(server.sin_addr));

  memset(&client, 0, sizeof(struct sockaddr_in));

  lenght = sizeof(struct sockaddr_in);

  int message =
      recvfrom(sock, packet, SIZE, 0, (struct sockaddr *)&client, &lenght);
  if (message < 0) {
    perror("error recieve");
    exit(1);
  }

  printf("Client IP: %s\n", inet_ntoa(client.sin_addr));
  printf("Client PORT: %d\n", ntohs(client.sin_port));
  printf("Bytes: %d\n", message);
  printf("Message from client: %s\n", packet);

  packet[0] = 'N';

  while (1) {
    message = sendto(sock, packet, strlen(packet) * sizeof(char), 0,
                     (struct sockaddr *)&client, lenght);

    if (message < 0) {
      perror("error send");
      exit(1);
    }
  }
  close(sock);
}