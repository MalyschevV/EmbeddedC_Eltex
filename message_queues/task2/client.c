#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 256
#define QUEUE_NAME "/my_queue"

int main() {
  mqd_t client;
  char buffer[MAX_MESSAGE_SIZE];

  client = mq_open(QUEUE_NAME, O_RDWR);
  if (client == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }

  printf("client started!\n");

  if (mq_send(client, "hello", sizeof("hello"), 0) == -1) {
    perror("mq_send");
    exit(1);
  }

  if (mq_receive(client, buffer, MAX_MESSAGE_SIZE, NULL) == -1) {
    perror("mq_receive");
    exit(1);
  }

  printf("server: %s\n", buffer);

  if (mq_close(client) == -1) {
    perror("mq_close");
    exit(1);
  }

  return 0;
}