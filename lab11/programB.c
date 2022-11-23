#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char msg[100];
    char tmp[110];
    key_t key1, key2;
    int qid1, qid2;
    
    key1 = 1111; key2 = 2222;
    qid1 = msgget(key1, IPC_CREAT | 0666);
    qid2 = msgget(key2, IPC_CREAT | 0666);

    while(1) {
        sleep(2);
        msgrcv(qid1, msg, 100, 0, 0);
        printf("String from program A: %s\n", msg);
        strcpy(tmp, msg);
        //printf("debug1: tmp = %s\n", tmp); // tmp == msg
        strcat(tmp, "Wooseok"); 
        //printf("debug2 tmp: %s\n", tmp); // tmp += "Wooseok"
        msgsnd(qid2, tmp, strlen(tmp) + 1, 0);
        if(!strcmp(msg, "end")) break;
        while(1) {
            sleep(2);
            if(strcmp(msg, tmp)) break;
        }
    } 
    printf("ProgramB end\n");
}
