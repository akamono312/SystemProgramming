#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void my_sig_handler(int signum) {
    printf("signum = %d\n", signum);
	printf("Signal is caught.\n");
}

void my_alarm_handler(int signum) {
    printf("signum = %d\n", signum);
	printf("Signal is caught.\n");
	alarm(5);
}

int main() {

	signal(SIGINT, my_sig_handler);
	signal(SIGUSR1, my_sig_handler);
	signal(SIGALRM, my_alarm_handler);

	alarm(5);

	while(1) {
		printf("Hello\n");
		sleep(2);
		//pause();
	}
}
