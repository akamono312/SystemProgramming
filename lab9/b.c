#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    printf("My pid in b.out = %d\n", getpid());
    for(i = 0; i < 10; i++) {
        sleep(1);
        printf("Hello.\n");
    }
}