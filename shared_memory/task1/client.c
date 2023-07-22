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

  key = ftok("server", 1337);
  shmid = shmget(key, SHM_SIZE, 0666);
  if (shmid == -1) {
    perror("shmget");
    return 1;
  }

  data = shmat(shmid, (void *)0, 0);
  if (data == (char *)(-1)) {
    perror("shmat");
    return 1;
  }

  strcpy(data, "hello");
  printf("Client: %s\n", data);

  while (strcmp(data, "hi") != 0) {
    
  }

  printf("Server: %s\n", data);

  shmdt(data);

  return 0;
}