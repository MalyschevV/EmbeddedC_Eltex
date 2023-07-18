#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE 12

int main() {
  int first_fd, second_fd;
  char* myfifo1 = "./tmp/myfifo1";
  char* myfifo2 = "./tmp/myfifo2";
  char first_message[SIZE] = "Hello!\n";
  char second_message[SIZE] = "Hi!\n";

  mkfifo(myfifo1, 0666);
  mkfifo(myfifo2, 0666);

  first_fd = open(myfifo1, O_RDONLY);
  second_fd = open(myfifo2, O_WRONLY);

  read(first_fd, first_message, SIZE);
  printf("read from first fifo: %s\n", first_message);

  write(second_fd, second_message, SIZE);
  printf("write for second fifo: %s\n,", second_message);

  close(first_fd);
  close(second_fd);

  unlink(myfifo1);
  unlink(myfifo2);

  return 0;
}