#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char msg[100];
    char tmp[110];
    int fd;
    
    fd = open("fifo1", O_RDWR);
    printf("fd = %d\n", fd);

    while(1) {
        sleep(2);
        read(fd, msg, 100);
        printf("String from program A: %s\n", msg);
        strcpy(tmp, msg);
        //printf("debug1: tmp = %s\n", tmp); // tmp == msg
        strcat(tmp, "Wooseok"); 
        //printf("debug2 tmp: %s\n", tmp); // tmp += "Wooseok"
        write(fd, tmp, strlen(tmp) + 1);
        if(!strcmp(msg, "end")) break;
        while(1) {
            sleep(2);
            if(strcmp(msg, tmp)) break;
        }
    } 
    printf("ProgramB end\n");
}
