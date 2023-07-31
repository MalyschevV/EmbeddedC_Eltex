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
#define MAX_CLIENTS 10

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

  pid_t thread_server_id = syscall(__NR_gettid);

  while (1) {
    if (recv(sock, buffer, SIZE, 0) < 0) {
      perror("Error recieve client message");
      exit(1);
    } else {
      printf("Server : message from client %sCurrent thread : %d\n", buffer,
             thread_server_id);

      char *time = getTime();
      char message_from_server[SIZE] = "Hello client! Current time :";
      strcpy(current_time, time);
      strcat(message_from_server, current_time);

      if (send(sock, message_from_server, SIZE, 0) < 0) {
        perror("error send to server");
        exit(1);
      }
      memset(message_from_server, 0, sizeof(message_from_server));
      memset(current_time, 0, sizeof(current_time));
    }
  }

  close(sock);

  return NULL;
}

int main() {
  pthread_t server_pool[MAX_CLIENTS];
  struct sockaddr_in addr;
  int num_of_clients = 0;

  int sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0) {
    perror("Error create server socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(7777);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
    perror("Error server bind");
    exit(1);
  }

  printf("Server: port - %d\n", ntohs(addr.sin_port));
  printf("SERVER: IP - %s\n", inet_ntoa(addr.sin_addr));

  if (listen(sock, MAX_CLIENTS)) {
    perror("Error server listen");
    exit(1);
  }

  while (1) {
    int client_fd = accept(sock, 0, 0);

    if (client_fd < 0) {
      perror("Fail accept\n");
      exit(1);
    }

    if (pthread_create(&server_pool[num_of_clients++], NULL, (void *)handler,
                       &client_fd) < 0) {
      perror("error create thread");
      exit(1);
    }

    if (num_of_clients >= MAX_CLIENTS) {
      int i = 0;
      if (pthread_join(server_pool[i++], NULL) < 0) {
        perror("error join thread");
        exit(1);
      }
      while (i < MAX_CLIENTS) {
        server_pool[i - 1] = server_pool[i];
        i++;
      }
      num_of_clients--;
    }
  }

  close(sock);
}