#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>


void fork_program(int ppid) {
    char *arglist[10];
    char buf[100];
    int status;
    int fork_rv;
    int i;
    i = 0;

    fork_rv = fork();
    if(fork_rv == -1) {
        perror("fork");
    } else if(fork_rv == 0) {
        while(i < 10) {
            printf("Wooseok Arg[%d]? ", i);
            gets(buf);
            if(strcmp(buf, "quit") == 0)  {
                kill(ppid, SIGINT);
                exit(1);
            }
            arglist[i] = (char*)malloc(strlen(buf) + 1);
            strcpy(arglist[i], buf);
            if (strcmp(arglist[i], "") == 0) {
                arglist[i] = NULL;
                execvp(arglist[0], arglist);
                exit(1);
            }
            i++;
        }
    } else {
        wait(&status);
        fork_program(ppid);
    }
}


int main() {
    printf("Input \"quit\" to quit the program\n");
    int parentPid = getpid();
    fork_program(parentPid);

    return 0;
}