#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define SIZE 100
#define NUM_OF_THREADS 2

struct message {
  long mtype;
  char mtext[SIZE];
};

void *SendMessage() {
  char buffer[SIZE];
  key_t key;
  int msqid;
  struct message msg;

  key = ftok("client", 555);

  msqid = msgget(key, 0666);
  if (msqid == -1) {
    printf("queue create\n");
    return NULL;
  }

  strcpy(msg.mtext, "New client connected\n");
  msg.mtype = 1;

  if (msgsnd(msqid, &msg, sizeof(msg), 0) == -1) {
    perror("msgsnd\n");
    return NULL;
  }

  while (1) {
    fgets(buffer, sizeof(buffer), stdin);
    strcpy(msg.mtext, buffer);

    msg.mtype = 1;

    if (msgsnd(msqid, &msg, sizeof(msg), 0) == -1) {
      perror("msgsnd\n");
      return NULL;
    }
  }
  return NULL;
}

void *RecieveMessage() {
  key_t key_for_other;
  int msqid_for_other;
  struct message msg_for_other;

  key_for_other = ftok("server", 777);

  msqid_for_other = msgget(key_for_other, 0666);
  if (msqid_for_other == -1) {
    perror("queue create\n");
    return NULL;
  }

  while (1) {
    if (msgrcv(msqid_for_other, &msg_for_other, sizeof(msg_for_other), 1, 0) ==
        -1) {
      perror("msgrcv client");
      return NULL;
    }

    printf("%s", msg_for_other.mtext);
  }
}

int main() {
  pthread_t client_thread[NUM_OF_THREADS];

  if (pthread_create(&client_thread[0], NULL, RecieveMessage, NULL) != 0) {
    printf("Failed to create recieve thread\n");
    return 1;
  }

  if (pthread_create(&client_thread[1], NULL, SendMessage, NULL) != 0) {
    printf("Failed to create send thread\n");
    return 1;
  }

  for (int i = 0; i < NUM_OF_THREADS; i++) {
    if (pthread_join(client_thread[i], NULL) != 0) {
      printf("Failed to join thread\n");
      return 1;
    }
  }

  return 0;
}