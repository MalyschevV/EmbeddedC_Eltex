#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SIZE 100

int main() {
  int sock = socket(AF_LOCAL, SOCK_DGRAM, 0);

  if (sock < 0) {
    perror("error server socket create");
    exit(1);
  }

  struct sockaddr_un addr;

  addr.sun_family = AF_LOCAL;
  strcpy(addr.sun_path, "client_socket");

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("error bind client socket");
    exit(1);
  }

  socklen_t len = sizeof(addr);

  struct sockaddr_un server_addr_p;

  server_addr_p.sun_family = AF_LOCAL;
  strcpy(server_addr_p.sun_path, "server_socket");

  char message_for_server[SIZE] = "hello!\n";

  if (sendto(sock, message_for_server, SIZE, 0,
             (struct sockaddr *)&server_addr_p, sizeof(server_addr_p)) < 0) {
    perror("cannot send message to server");
    exit(1);
  }

  char buffer[SIZE];
  socklen_t lenght = sizeof(server_addr_p);
  bzero(&buffer, SIZE);

  int message = recvfrom(sock, &buffer, SIZE, 0,
                         (struct sockaddr *)&server_addr_p, &lenght);
  if (message < 0) {
    perror("error recieve message");
    exit(1);
  }

  printf("Client: message from server: %s\n", buffer);
}