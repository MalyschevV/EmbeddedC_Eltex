#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define SIZE 127
#define PORT 8888
#define GROUP "239.0.0.1"
#define SLEEP_TIME 2

int main() {
  char buffer[SIZE] = "hello group!\n";
  struct sockaddr_in server;

  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0) {
    perror("error create socket");
    exit(1);
  }

  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = inet_addr(GROUP);
  int serverlenght = sizeof(server);

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