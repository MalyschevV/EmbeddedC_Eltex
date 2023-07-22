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
  char *response = "hi";

  shm_fd = shm_open("shm", O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open");
    return 1;
  }

  ftruncate(shm_fd, SHM_SIZE);

  data = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (data == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  while (1) {
    if (strcmp(data, "hello") == 0) {
      printf("Client: %s\n", data);
      strcpy(data, response);
      printf("Server: %s\n", response);
    }
  }

  munmap(data, SHM_SIZE);
  close(shm_fd);
  shm_unlink("shm");

  return 0;
}