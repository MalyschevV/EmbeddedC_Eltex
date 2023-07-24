#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 100
#define SLEEP_TIME 3

typedef struct messagebuf {
  long mtype;
  char mtext[SIZE];
} messagebuf;

int main() {
  messagebuf message;
  key_t key;
  int msgqueue_id;
  pid_t proccess;

  key = ftok("server", 1337);

  if (msgqueue_id = msgget(key, IPC_CREAT | 0660) == -1) {
    perror("msgget");
    exit(1);
  }
  message.mtype = 1;

  if (msgrcv(msgqueue_id, &message, SIZE, 2, 0) == -1) {
    perror("msgrcv");
    exit(1);
  }

  printf("Server sent its pid to complete : %s\n", message.mtext);

  printf("Processing...\n");

  proccess = atoi(message.mtext);

  while (1) {
    kill(proccess, SIGUSR1);
    sleep(SLEEP_TIME);
  }

  return 0;
}