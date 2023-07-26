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
  char buffer[SIZE];
  int message;
  char message_for_server[SIZE] = "hello!\n";

  int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("create client socket");
    exit(1);
  }

  struct sockaddr_un addr;

  addr.sun_family = AF_LOCAL;
  strcpy(addr.sun_path, "./server.c");

  struct sockaddr_un server_addr;

  server_addr.sun_family = AF_LOCAL;
  strcpy(server_addr.sun_path, "server_socket");

  int socket_connect =
      connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if (socket_connect < 0) {
    perror("Fail connect to server");
    exit(1);
  }

  if (send(sock, message_for_server, SIZE, 0) < 0) {
    perror("error send messade for server");
    exit(1);
  }

  if ((message = recv(sock, buffer, SIZE, 0)) < 0) {
    perror("error send form server");
    exit(1);
  }

  printf("Client: message from server: %s\n", buffer);
}
