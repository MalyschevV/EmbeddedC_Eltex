#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 20
#define SLEEP_TIME 2

int main() {
  int first_fd[2];
  int second_fd[2];
  pid_t proccess;
  char parent_message[SIZE] = "Hello!\n";
  char child_message[SIZE] = "Hi!\n";
  char first_buffer[SIZE];
  char second_buffer[SIZE];
  

  pipe(first_fd);
  pipe(second_fd);

  proccess = fork();
  if (proccess < 0) {
    fprintf(stderr, "Error create child\n");
    return 1;
  } else if (proccess > 0) {
    close(first_fd[0]);
    write(first_fd[1], parent_message, SIZE);
    printf("Parent write message in first pipe \n");
    close(second_fd[1]);
  } else {
    close(second_fd[0]);
    close(first_fd[1]);
    printf("Child read message in first pipe \n");
    read(first_fd[0], first_buffer, SIZE);
    printf("%s\n", first_buffer);
    close(first_fd[0]);
    printf("Child write message in second pipe\n");
    write(second_fd[1], child_message, SIZE);
    close(second_fd[1]);
  }

  sleep(SLEEP_TIME);
  if (proccess > 0) {
    close(second_fd[1]);
    printf("Parent read message in second pipe\n");
    read(second_fd[0], second_buffer, SIZE);
    printf("%s\n", second_buffer);
    close(second_fd[0]);
  }

  return 0;
}