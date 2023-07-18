#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main() {
  char command[MAX_COMMAND_LENGTH];

  while (1) {
    printf("$: ");
    fgets(command, MAX_COMMAND_LENGTH, stdin); 

    if (command[strlen(command) - 1] == '\n') {
      command[strlen(command) - 1] = '\0';
    }

    char *arguments[MAX_ARGUMENTS];
    int i = 0;
    char *token = strtok(command, " ");
    while (token != NULL) {
      arguments[i++] = token;
      token = strtok(NULL, " ");
    }
    arguments[i] = NULL;

    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      exit(1);
    } else if (pid == 0) {
      execvp(arguments[0], arguments);
      perror("execvp");
      exit(1);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }

  return 0;
}