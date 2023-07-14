#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

int main() {
  char command[MAX_COMMAND_LENGTH];
  char *args[MAX_ARGS];
  int status;
  int args_count = 0;

  while (1) {
    printf("$ ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    command[strcspn(command, "\n")] = 0;

    if (strcmp(command, "exit") == 0) {
      break;
    }

    char *token = strtok(command, " ");
    while (token != NULL && args_count < MAX_ARGS - 1) {
      args[args_count++] = token;
      token = strtok(NULL, " ");
    }
    args[args_count] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
      execvp(args[0], args);
      perror("Error");
      exit(EXIT_FAILURE);
    } else if (pid < 0) {
      perror("Error");
      exit(EXIT_FAILURE);
    } else {
      wait(&status);
    }
  }

  return 0;
}
