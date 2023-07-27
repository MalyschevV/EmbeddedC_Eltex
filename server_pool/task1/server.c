#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 128

char *getTime() {
  time_t mytime = time(NULL);
  char *time_str = ctime(&mytime);
  time_str[strlen(time_str) - 1] = '\0';
  return time_str;
}

void *handler(void *socket) {
  int sock = *(int *)socket;
  char buffer[SIZE];
  char current_time[SIZE];
  char message_from_server[SIZE] = "Hello client! Current time :";

  pid_t thread_server_id = syscall(__NR_gettid);

  while (1) {
    if (recv(sock, buffer, SIZE, 0) < 0) {
      perror("Error recieve client message");
      exit(1);
    } else {
      printf("Server : message from client %sCurrent thread : %d\n", buffer,
             thread_server_id);

      char *time = getTime();
      strcpy(current_time, time);
      strcat(message_from_server, current_time);

      if (send(sock, message_from_server, SIZE, 0) < 0) {
        perror("error send to server");
        exit(1);
      }
    }
  }

  close(sock);

  return NULL;
}

int main() {
  pthread_t server_thread;
  struct sockaddr_in addr;

  int sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0) {
    perror("Error create server socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(8888);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
    perror("Error server bind");
    exit(1);
  }

  printf("Server: port - %d\n", ntohs(addr.sin_port));
  printf("SERVER: IP - %s\n", inet_ntoa(addr.sin_addr));

  if (listen(sock, 5)) {
    perror("Error server listen");
    exit(1);
  }

  while (1) {
    int client_fd = accept(sock, 0, 0);

    if (client_fd < 0) {
      perror("Fail accept\n");
      exit(1);
    }

    if (pthread_create(&server_thread, NULL, (void *)handler, (void *)&client_fd) <
        0) {
      perror("Pthread creating failed");
      exit(1);
    }
  }

  if (pthread_join(server_thread, NULL) != 0) {
    perror("Failed to join thread");
    exit(1);
  }

  close(sock);
}
