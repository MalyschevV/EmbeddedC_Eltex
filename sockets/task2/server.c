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
  int message;
  char buffer[SIZE];
  char message_for_client[SIZE] = "Hi!\n";

  int sock = socket(AF_INET, SOCK_STREAM, 0);

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

  if (listen(sock, 5)) {
    perror("error listen");
    exit(1);
  }

  int socket_accept = accept(sock, 0, 0);

  if (socket_accept < 0) {
    perror("Fail accept");
    exit(1);
  }

  if ((message = recv(socket_accept, buffer, SIZE, 0)) < 0) {
    perror("error recieve from client");
    exit(1);
  }

  printf("SERVER: message from client: %s\n", buffer);

  sleep(SLLEP_TIME);

  if (send(socket_accept, message_for_client, SIZE, 0) < 0) {
    perror("error send to client");
    exit(1);
  }

  close(sock);
}