#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SIZE 100

int main(int argc, char* argv[]) {
  char buffer[SIZE];
  int message;
  char message_for_server[SIZE] = "hello!\n";

  if (argc != 3) {
    perror("to few command arguments");
    exit(1);
  }

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("create client socket");
    exit(1);
  }

  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(8888);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  socklen_t len = sizeof(addr);

  struct sockaddr_in server_addr_p;

  server_addr_p.sin_family = AF_INET;
  server_addr_p.sin_port = htons(atoi(argv[2]));

  inet_pton(AF_INET, argv[1], &server_addr_p.sin_addr);

  int socket_connect =
      connect(sock, (struct sockaddr*)&server_addr_p, sizeof(server_addr_p));

  if (socket_connect < 0) {
    perror("Fail connect to server");
    exit(1);
  }

  if (send(sock, message_for_server, SIZE, 0) < 0) {
    perror("error send to server");
    exit(1);
  }

  if ((message = recv(sock, buffer, SIZE, 0)) < 0) {
    perror("error send form server");
    exit(1);
  }

  printf("Client: message from server: %s\n", buffer);
}