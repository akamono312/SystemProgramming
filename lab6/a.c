#include <stdio.h>
#include <unistd.h>

int main() {
	int i;
	for(i = 0; i < 100; i++) {
		printf("Hello\n");
		sleep(2);
	}
}
