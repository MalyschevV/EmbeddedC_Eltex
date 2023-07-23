#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SIZE 100
#define MAX_CLIENTS 5

struct message {
  long mtype;
  char mtext[SIZE];
  int client_id;
};

int main() {
  key_t key, key_for_other;
  int msqid, msqid_for_other;
  struct message msg_for_other;
  struct message msg;
  struct msqid_ds buf;
  int num_of_clients = 0;

  key = ftok("client", 555);

  msqid = msgget(key, 0666 | IPC_CREAT);
  if (msqid == -1) {
    printf("queue create\n");
    return 1;
  }

  key_for_other = ftok("server", 777);

  msqid_for_other = msgget(key_for_other, 0666 | IPC_CREAT);
  if (msqid_for_other == -1) {
    printf("queue create\n");
    return 1;
  }

  msg_for_other.mtype = 1;

  while (1) {
    if (msgrcv(msqid, &msg, sizeof(msg), 1, 0) == -1) {
      perror("msgrcv server");
      return 1;
    }

    if (strcmp(msg.mtext, "New client connected\n") == 0) {
      num_of_clients++;
      if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        return 1;
      }
      printf("current quantity clients: %d\n", num_of_clients);
    }

    printf("%s", msg.mtext);
    strcpy(msg_for_other.mtext, msg.mtext);

    msg_for_other.client_id = msg.client_id;
    
    for (int i = 0; i < num_of_clients; i++) {
      if (msgsnd(msqid_for_other, &msg_for_other, sizeof(msg_for_other), 0) ==
          -1) {
        perror("msgsnd server");
        return 1;
      }
    }
  }

  msgctl(msqid, IPC_RMID, NULL);
  msgctl(msqid_for_other, IPC_RMID, NULL);

  return 0;
}