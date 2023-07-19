#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 10
#define MAX_COMMANDS 10
#define LENGTH 100

int main() {
  char input[LENGTH];
  char *args[MAX_ARGS];
  char *commands[MAX_COMMANDS][MAX_ARGS];
  int num_commands = 0;
  char *token;
  int pipefd[2];
  int pipe_index;
  pid_t first_process;
  pid_t second_proccess;

  while (1) {
    printf("$: ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0;

    token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
      args[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    args[i] = NULL;

    pipe_index = -1;
    for (int j = 0; j < i; j++) {
      if (strcmp(args[j], "|") == 0) {
        pipe_index = j;
        break;
      }
    }
    if (pipe_index == -1) {
      pid_t pid = fork();
      if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(1);
      } else {
        wait(NULL);
      }
    } else {
      for (int j = 0; j < pipe_index; j++) {
        commands[num_commands][j] = args[j];
      }
      commands[num_commands][pipe_index] = NULL;
      num_commands++;
      for (int j = pipe_index + 1; j < i; j++) {
        commands[num_commands][j - pipe_index - 1] = args[j];
      }
      commands[num_commands][i - pipe_index - 1] = NULL;
      num_commands++;

      if (num_commands > 2) {
        printf("only one symbol \"|\"\n");
        num_commands = 0;
        continue;
      }

      if (pipe(pipefd) == -1) {
        perror("pipe create");
        exit(1);
      }

      first_process = fork();
      if (first_process == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execvp(commands[0][0], commands[0]);
        perror("execvp");
        exit(1);
      } else if (first_process < 0) {
        perror("fork");
        exit(1);
      }

      second_proccess = fork();
      if (second_proccess == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execvp(commands[1][0], commands[1]);
        perror("execvp");
        exit(1);
      } else if (second_proccess < 0) {
        perror("second fork");
        exit(1);
      }

      close(pipefd[0]);
      close(pipefd[1]);

      waitpid(first_process, NULL, 0);
      waitpid(second_proccess, NULL, 0);

      num_commands = 0;
    }
  }

  return 0;
}