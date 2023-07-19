#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 256
#define MAX_MESSAGES 100
#define QUEUE_NAME "/my_queue"

int main() {
  mqd_t qd_server;
  struct mq_attr attr;
  char buffer[MAX_MESSAGE_SIZE];

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = MAX_MESSAGE_SIZE;
  attr.mq_curmsgs = 0;

  qd_server = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
  if (qd_server == (mqd_t)-1) {
    perror("mq_open");
    exit(1);
  }

  printf("qd_server started!\n");

  if (mq_receive(qd_server, buffer, MAX_MESSAGE_SIZE, NULL) == -1) {
    perror("qd_server mq_receive");
    exit(1);
  }

  printf("client: %s\n", buffer);

  if (mq_send(qd_server, "hi", sizeof("hi"), 0) == -1) {
    perror("qd_server mq_send");
    exit(1);
  }

  if (mq_close(qd_server) == -1) {
    perror("qd_server mq_close");
    exit(1);
  }

  if (mq_unlink(QUEUE_NAME) == -1) {
    perror("qd_server mq_unlink");
    exit(1);
  }

  return 0;
}