#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char msg[100];
    char tmp[110];
    int fd;
    int i = 0;
    int nread;
    
    fd = open("fifo1", O_RDWR);
    printf("fd = %d\n", fd);


    while(1) {
        printf("Enter a string: ");
        gets(msg);
        if(!strcmp(msg, "end")) i = 1;
        nread = write(fd, msg, strlen(msg) + 1);
        while(1) {
            sleep(2);
            read(fd, tmp, 110);
            if(strcmp(msg, tmp)) break;
        }
        printf("String from program B: %s\n", tmp);
        if(i == 1) break;
    }
    printf("Program A end\n");
}
