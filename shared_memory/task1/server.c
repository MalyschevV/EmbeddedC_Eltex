#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
  key_t key;
  int shmid;
  char *data;
  char *response = "hi";

  key = ftok("server", 1337);
  shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
  if (shmid == -1) {
    perror("shmget");
    return 1;
  }

  data = shmat(shmid, (void *)0, 0);
  if (data == (char *)(-1)) {
    perror("shmat");
    return 1;
  }

  while (1) {
    if (strcmp(data, "hello") == 0) {
      printf("Client: %s\n", data);
      strcpy(data, response);
      printf("Server: %s\n", response);
    }
  }

  shmdt(data);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}