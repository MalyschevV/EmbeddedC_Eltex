#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SIZE 127
#define PORT 8888
#define BROADCAST_IP "255.255.255.255"
#define SLEEP_TIME 2

int main() {
  char buffer[SIZE] = "hello from broadcast!\n";
  struct sockaddr_in server;

  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0) {
    perror("error create socket");
    exit(1);
  }

  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = inet_addr(BROADCAST_IP);
  int serverlenght = sizeof(server);

  int broadcast_enable = 1;

  if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast_enable,
                 sizeof(broadcast_enable)) == -1) {
    perror("error socket option");
    exit(1);
  }

  while (1) {
    if (sendto(sock, buffer, SIZE, 0, (struct sockaddr*)&server,
               sizeof(server)) < 0) {
      perror("error send");
      exit(1);
    }
    sleep(SLEEP_TIME);
  }

  close(sock);
}