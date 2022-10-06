#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
struct Node {
	int a;
	float b;
	char name[12];
};

int main ()
{
	int fd;
	struct Node node;
	node.a = 10;
	node.b = 3.14;
	strcpy (node.name, "Kim");
	fd = open ("bbb.data", O_RDWR | O_CREAT);
	write (fd, &node, sizeof(struct Node));
	close (fd);
}