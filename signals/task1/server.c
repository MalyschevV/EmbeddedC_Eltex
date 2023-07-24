#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 100

typedef struct messagebuf {
  long mtype;
  char mtext[SIZE];
} messagebuf;

int main() {
  messagebuf message;
  key_t key;
  int msgqueue_id;
  pid_t proccess;
  char buffer[SIZE];

  key = ftok("server", 1337);

  if (msgqueue_id = msgget(key, IPC_CREAT | 0660) == -1) {
    perror("msgget");
    exit(1);
  }

  printf("Queue successfully created!\n");

  proccess = getpid();

  printf("I am a server with a process id = %d\n", proccess);

  sprintf(buffer, "%d", proccess);

  strcpy(message.mtext, buffer);

  message.mtype = 2;

  if (msgsnd(msgqueue_id, &message, sizeof(message.mtext), 0) == -1) {
    perror("msgsnd");
    exit(1);
  }

  printf("waiting for the end ...\n");

  while (1) {
  }

  return 0;
}