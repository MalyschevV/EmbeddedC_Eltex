#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SIZE 128

int main(int argc, char* argv[]) {
  if (argc != 3) {
    perror("to few command arguments");
    exit(1);
  }

  char message_for_server[SIZE];

  int sock = socket(AF_INET, SOCK_DGRAM, 0);
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

  while (1) {
    fgets(message_for_server, SIZE, stdin);
    if (sendto(sock, message_for_server, SIZE, 0,
               (struct sockaddr*)&server_addr_p, sizeof(server_addr_p)) < 0) {
      perror("cannot send message to server");
      exit(1);
    } else {
      char buffer[SIZE];
      socklen_t lenght = sizeof(server_addr_p);
      bzero(&buffer, SIZE);

      int message = recvfrom(sock, &buffer, SIZE, 0,
                             (struct sockaddr*)&server_addr_p, &lenght);
      if (message < 0) {
        perror("error recieve message");
        exit(1);
      }
      printf("Client: message from server: %s\n", buffer);
    }
  }
}