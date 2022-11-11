#include <stdio.h>
#include <fcntl.h>

int main() {
	int fd, pid;
	fd = open("test.txt", O_RDWR | O_CREAT, 0666);
	printf("fd = %d \n", fd);
	pid = fork();
	if(pid == 0) {
		sleep(2); 
		write(fd, "hello in CH\n", strlen("hello in CH\n") + 1);
	}
	else {
		sleep(2); 
		write(fd, "hi in PA\n", strlen("hi in PA\n") + 1);
	}
}