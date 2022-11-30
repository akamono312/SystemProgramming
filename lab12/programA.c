#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <string.h>

int main() {
    char msg[100];
    char tmp[110];
    sem_t *sem1, *sem2;
    int shmid;
    int* shmaddr;
    int i = 0;
    key_t key;

    key = 1111;
    shmid = shmget(key, 110, IPC_CREAT | 0666);
    shmaddr = shmat(shmid, 0, 0);
    sem1 = sem_open("semA", O_CREAT, 0666, 1);
    sem2 = sem_open("semB", O_CREAT, 0666, 1);

    while(1) {
        sem_wait(sem1);
        printf("Enter a string: ");
        gets(msg);
        if(!strcmp(msg, "end")) i = 1;

        strcpy((char*)shmaddr, msg);

        sem_post(sem1); // go to programB
        sleep(3);

        sem_wait(sem2); // wait for programB
        

        strcpy(tmp, (char*)shmaddr);
        printf("String from program B: %s\n", tmp);
        sem_post(sem2);
        if(i == 1) break;
    }
    shmdt(shmaddr);
    printf("Program A end\n");
}
