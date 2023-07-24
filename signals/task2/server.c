#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 100
#define SLEEP_TIME 2

typedef struct messagebuf {
  long mtype;
  char mtext[SIZE];
} messagebuf;

void handle_signal(int sig) {
  if (sig == SIGUSR1) {
    printf("Server received a signal from the client...\n");
  }
}

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

  printf("waiting for the signal ...\n");

  signal(SIGUSR1, handle_signal);

  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  while (1) {
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
  }

  return 0;
}