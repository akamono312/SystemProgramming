#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char msg[100];
    char tmp[110];
    int qid1, qid2;
    int i = 0;
    int nread;
    key_t key1, key2;

    key1 = 1111; key2 = 2222;
    qid1 = msgget(key1, IPC_CREAT | 0666);
    qid2 = msgget(key2, IPC_CREAT | 0666);

    while(1) {
        printf("Enter a string: ");
        gets(msg);
        if(!strcmp(msg, "end")) i = 1;
        msgsnd(qid1, msg, strlen(msg) + 1, 0);
        while(1) {
            sleep(2);
            msgrcv(qid2, tmp, 110, 0, 0);
            if(strcmp(msg, tmp)) break;
        }
        printf("String from program B: %s\n", tmp);
        if(i == 1) break;
    }
    printf("Program A end\n");
}
