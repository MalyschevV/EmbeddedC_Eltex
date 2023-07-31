#include <arpa/inet.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define SIZE 128

char *getTime() {
  time_t mytime = time(NULL);
  char *time_str = ctime(&mytime);
  time_str[strlen(time_str) - 1] = '\0';
  return time_str;
}

int main(void) {
  int tcp_server_socket, udp_server_socket;
  socklen_t address_length;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  struct sockaddr_in arr_address[FD_SETSIZE];
  fd_set readfds, fdlist;
  char current_time[SIZE];

  if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Error creating TCP socket");
    exit(1);
  }

  if ((udp_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Error creating UDP socket");
    exit(1);
  }

  bzero((char *)&server_address, sizeof(server_address));

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  server_address.sin_port = htons(8888);

  if (bind(tcp_server_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    perror("Error binding TCP socket");
    exit(1);
  }

  if (bind(udp_server_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    perror("Error binding UDP socket");
    exit(1);
  }

  address_length = sizeof(server_address);

  printf("Server: port - %d\n", ntohs(server_address.sin_port));
  printf("SERVER: IP - %s\n", inet_ntoa(server_address.sin_addr));

  if (listen(tcp_server_socket, 5) < 0) {
    perror("Error listening on TCP socket");
    exit(1);
  }

  FD_ZERO(&fdlist);
  FD_SET(tcp_server_socket, &fdlist);
  FD_SET(udp_server_socket, &fdlist);

  char *buffer = (char *)malloc(SIZE);
  while (1) {
    memcpy(&readfds, &fdlist, sizeof(fdlist));
    select(FD_SETSIZE, &readfds, NULL, NULL, NULL);

    if (FD_ISSET(tcp_server_socket, &readfds)) {
      int client_socket =
          accept(tcp_server_socket, (struct sockaddr *)(&client_address),
                 &address_length);

      memcpy(&arr_address[client_socket], &client_address,
             sizeof(client_address));
      FD_SET(client_socket, &fdlist);

      printf("TCP client connected: %s:%d\n",
             inet_ntoa(client_address.sin_addr),
             ntohs(client_address.sin_port));
    }

    if (FD_ISSET(udp_server_socket, &readfds)) {
      int num_bytes =
          recvfrom(udp_server_socket, buffer, SIZE, 0,
                   (struct sockaddr *)&client_address, &address_length);
      if (num_bytes > 0) {
        printf("UDP message received from %s:%d: %s\n",
               inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port), buffer);

        char message_from_server[SIZE] = "Hello client! Current time :";
        char *time = getTime();
        strcpy(current_time, time);
        strcat(message_from_server, current_time);

        if (sendto(udp_server_socket, message_from_server, SIZE, 0,
                   (struct sockaddr *)&client_address,
                   sizeof(client_address)) < 0) {
          perror("error sendto");
          exit(1);
        }
        memset(message_from_server, 0, sizeof(message_from_server));
        memset(current_time, 0, sizeof(current_time));
      }
    }

    for (int fd = 0; fd < FD_SETSIZE; fd++) {
      if (FD_ISSET(fd, &readfds) && fd != tcp_server_socket &&
          fd != udp_server_socket) {
        int num_bytes = recv(fd, buffer, SIZE, 0);
        if (num_bytes > 0) {
          memcpy(&client_address, &arr_address[fd], sizeof(arr_address[fd]));

          printf("TCP client message from %s:%d: %s\n",
                 inet_ntoa(client_address.sin_addr),
                 ntohs(client_address.sin_port), buffer);

          char message_from_server[SIZE] = "Hello client! Current time :";
          char *time = getTime();
          strcpy(current_time, time);
          strcat(message_from_server, current_time);

          if (send(fd, message_from_server, SIZE, 0) < 0) {
            perror("Error sending TCP response to client");
            exit(1);
          }
          memset(message_from_server, 0, sizeof(message_from_server));
          memset(current_time, 0, sizeof(current_time));
        } else {
          FD_CLR(fd, &fdlist);

          memcpy(&client_address, &arr_address[fd], sizeof(arr_address[fd]));
          printf("TCP client disconnected: %s:%d\n",
                 inet_ntoa(client_address.sin_addr),
                 ntohs(client_address.sin_port));

          memset(&arr_address[fd], 0, sizeof(arr_address[fd]));
          close(fd);
        }
      }
    }
  }
  return 0;
}