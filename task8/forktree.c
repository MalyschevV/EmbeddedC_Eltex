#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void GetInfo(pid_t proccess) {
  printf("im child %d\n", getpid());
  printf("my parent %d\n", getppid());
  printf("\n");
}

int main() {
  pid_t first_child, second_child, third_child, fourth_child, fifth_child;
  int first_status, second_status, third_status, fourth_status, fifth_status;

  first_child = fork();

  if (first_child > 0) {
    printf("im parent %d\n\n", getpid());
    second_child = fork();
    if (second_child == 0) {
      GetInfo(second_child);
      fifth_child = fork();
      if (fifth_child > 0) {
      } else if (fifth_child == 0) {
        GetInfo(fifth_child);
        exit(0);
      } else {
        fprintf(stderr, "Error create fifth child\n");
        return 1;
      }
      waitpid(fifth_child, &fifth_status, 0);
      exit(0);
    } else if (second_child > 0) {
    } else {
      fprintf(stderr, "Error create second child\n");
      return 1;
    }
    waitpid(first_child, &first_status, 0);
    waitpid(second_child, &second_status, 0);
  } else if (first_child == 0) {
    GetInfo(first_child);
    third_child = fork();
    if (third_child > 0) {
      fourth_child = fork();
      if (fourth_child > 0) {
      } else if (fourth_child == 0) {
        GetInfo(fourth_child);
        exit(0);
      } else {
        fprintf(stderr, "Error create fourth child\n");
        return 1;
      }
    } else if (third_child == 0) {
      GetInfo(third_child);
      exit(0);
    } else {
      fprintf(stderr, "Error create third child\n");
      return 1;
    }
    waitpid(third_child, &third_status, 0);
    waitpid(fourth_child, &fourth_status, 0);
    exit(0);
  } else {
    fprintf(stderr, "Error create first child\n");
    return 1;
  }
}
