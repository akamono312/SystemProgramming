#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
	char msg[100];
	int fd;
	int nread;

	fd = open("fifo1", O_WRONLY);
	printf("fd = %d \n", fd);
	
	printf("Enter a string : ");
	gets(msg);
	nread = write(fd, msg, strlen(msg) + 1);

	sleep(2);
	printf("nread = %d \n", nread);
	write(fd, &nread, sizeof(int));

}