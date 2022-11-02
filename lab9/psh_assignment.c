#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void init_arglist(char* *arglist[10]) {
    int i;
    for(i = 0; i < 10; i++) {
        arglist[i] = NULL;
    }
}

int main() {
    char *arglist[10];
    char buf[100];
    int i;
    i = 0;
    while(i < 10) {
        printf("Wooseok Arg[%d]? ", i);
        gets(buf);
        if(strcmp(buf, "-1") == 0) break;
        arglist[i] = (char*) malloc(strlen(buf) + 1);
        strcpy(arglist[i], buf);
        if (strcmp(arglist[i], "") == 0) {
            arglist[i] = NULL;
            execvp(arglist[0], arglist);
            init_arglist(&arglist);
            i = -1;
        }
        i++;
    }
    execvp(arglist[0], arglist);
}