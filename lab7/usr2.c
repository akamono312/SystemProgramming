#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int result;
pid_t mypid, otherpid;

void my_sig_handler(int signum) {
    printf("SIGUSR2 signal is caught.\n");
    printf("send signal SIGUSR1 to usr1\n");
    result = kill(otherpid, SIGUSR1);
    printf("result = %d\n", result);
    exit(0);
}

int main() {
    int result;

    signal(SIGUSR2, my_sig_handler);

    mypid = getpid();
    printf("pid = %d\n", mypid);
    printf("enter the usr1's pid: ");
    scanf("%d", &otherpid);

    while(1) {
        printf("usr2 is running\n");
        sleep(2);
    }
}