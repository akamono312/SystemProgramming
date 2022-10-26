#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int pid, sig_num, result;

    if(argc != 3) {
        printf("Needs pid sig_num\n");
        exit(0);
    }

    pid = atoi(argv[1]);
    sig_num = atoi(argv[2]);
    result = kill(pid, sig_num);
    printf("result = %d\n", result);
}