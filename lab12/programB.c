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
    int shmid;
    int* shmaddr;
    key_t key;
    sem_t *sem1, *sem2;
    
    key = 1111;
    shmid = shmget(key, 110, IPC_CREAT | 0666);
    shmaddr = shmat(shmid, 0, 0);
    sem1 = sem_open("semA", O_CREAT, 0666, 1);
    sem2 = sem_open("semB", O_CREAT, 0666, 1);

    
    while(1) {
        sem_wait(sem2);
        sem_wait(sem1); // wait for programA
        strcpy(msg, (char*)shmaddr);
        printf("String from program A: %s\n", msg);
        sem_post(sem1);
        sleep(2);

        strcpy(tmp, msg);
        strcat(tmp, "Wooseok");
        
        strcpy((char*)shmaddr, tmp);

        sem_post(sem2); // go to programA
        

        if(!strcmp(msg, "end")) break;
        sleep(2);

    } 
    shmdt(shmaddr);
    printf("ProgramB end\n");
}
