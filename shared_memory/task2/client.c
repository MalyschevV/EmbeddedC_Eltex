#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
  int shm_fd;
  char *data;

  shm_fd = shm_open("shm", O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open");
    return 1;
  }

  data = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (data == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  strcpy(data, "hello");
  printf("Client: %s\n", data);

  while (strcmp(data, "hi") != 0) {

  }

  printf("Server: %s\n", data);

  munmap(data, SHM_SIZE);
  close(shm_fd);

  return 0;
}