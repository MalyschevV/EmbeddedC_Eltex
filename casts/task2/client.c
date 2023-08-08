#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define SIZE 127
#define PORT 8888

int main() {
  char buffer[SIZE];
  struct sockaddr_in client;
  struct sockaddr_in server;

  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0) {
    perror("error create socket");
    exit(1);
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(PORT);
  client.sin_addr.s_addr = htonl(INADDR_ANY);

  int serverlenght = sizeof(server);

  if (bind(sock, (struct sockaddr*)&client, sizeof(client)) < 0) {
    perror("error bind");
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