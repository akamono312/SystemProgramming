#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void my_sig_handler(int signum) {
    printf("SIGUSR1 signal is caught.\n");
    exit(0);
}

int main() {
    int result;
    pid_t mypid, otherpid;

    signal(SIGUSR1, my_sig_handler);

    mypid = getpid();
    printf("pid = %d\n", mypid);
    printf("enter the usr2's pid: ");
    scanf("%d", &otherpid);


    while(1) {
        printf("usr1 is running\n");
        sleep(2);
        
        printf("send signal SIGUSR2 to usr2\n");
        result = kill(otherpid, SIGUSR2);
        printf("result = %d\n", result);
    }
}