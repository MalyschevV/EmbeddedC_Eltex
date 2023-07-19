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
  key = ftok("server", 1337);

  if (msgqueue_id = msgget(key, IPC_CREAT | 0660) == -1) {
    perror("msgget");
    exit(1);
  } else {
    printf("Queue successfully created!\n");
  }

  if (msgrcv(msgqueue_id, &message, SIZE, 1, 0) == -1) {
    perror("msgrcv");
    exit(1);
  }

  printf("Client: %s\n", message.mtext);

  strcpy(message.mtext, "Hello!\n");

  message.mtype = 2;

  if (msgsnd(msgqueue_id, &message, sizeof(message.mtext), 0) == -1) {
    perror("msgsnd");
    exit(1);
  }
  
  return 0;
}