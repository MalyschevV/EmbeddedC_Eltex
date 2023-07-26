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
#define SLLEP_TIME 2

int main() {
  int sock = socket(AF_LOCAL, SOCK_STREAM, 0);

  if (sock < 0) {
    perror("error server socket create");
    exit(1);
  }

  struct sockaddr_un addr;

  addr.sun_family = AF_LOCAL;
  strcpy(addr.sun_path, "server_socket");

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("error bind server socket");
    exit(1);
  }

  if (listen(sock, 5)) {
    perror("error listen");
    exit(1);
  }

  int client_fd;
  int message;
  int lenght;
  char buffer[SIZE];
  char message_for_client[SIZE] = "Hi!\n";
  struct sockaddr_un client_addr;

  lenght = sizeof(client_addr);

  client_fd = accept(sock, 0, 0);

  if (message = recv(client_fd, buffer, SIZE, 0) < 0) {
    perror("error reciever message from client");
    exit(1);
  }

  printf("Server: recieved message from client: %s\n", buffer);

  sleep(SLLEP_TIME);

  if (send(client_fd, message_for_client, SIZE, 0) < 0) {
    perror("error send message for client");
  }

  close(sock);
}