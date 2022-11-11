#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
	char msg[100];
	int fd;
	int nread, data;

	fd = open("fifo1", O_RDWR);
	printf("fd = %d \n", fd);
	
	nread = read (fd, msg, 100);
	printf("READER : %s \n", msg);
	nread = read (fd, &data, sizeof(int));
	printf("READER data = %d\n", data);
}