#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {

    pid_t pid;
    int status_code = 0;
    switch(pid = fork()) {
        case -1:
            perror("fork = -1");
            exit(1);
        case 0:
            printf("CHILD : Child process\n");
            printf("CHILD : PID %d\n", getpid());
            printf("CHILD : Parent pid %d\n", getppid());
            printf("CHILD : exit!\n");
            exit(status_code);
        default:
            printf("PARENT: Parent process!\n");
            printf("PARENT: PID %d\n", getpid());
            printf("PARENT: Child pid %d\n",pid);
            wait(NULL);
            printf("PARENT: Exit chid status: %d\n", WEXITSTATUS(status_code));
            printf("PARENT: exit!\n");
    }

}