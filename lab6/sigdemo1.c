#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void my_sig_handler(int signum) {
    printf("signum = %d\n", signum);
    printf("Hi..... this is a new signal handler.\n");
    printf("장우석\n");
}

int main() {

    signal(SIGINT, my_sig_handler); // signum 10

    for(int i = 0; i < 100; i++) {
        printf("Hello\n");
        sleep(2);
    }
}