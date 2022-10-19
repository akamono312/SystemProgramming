#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

int callcnt;

void my_alarm_handler(int signum) {
    callcnt += 1;
    
    time_t ct;
    struct tm tm;
    ct = time(NULL);
    tm = *localtime(&ct);
    
    printf("장우석\n");
    printf("%d-%d-%d\nH: %d, M: %d, S: %d\n", 
    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    if(callcnt == 3) exit(0);

    alarm(5);
}

int main() {
    int i;
    
    signal(SIGALRM, my_alarm_handler);

    alarm(5);
    while(1) {
        sleep(1);
    }
}
