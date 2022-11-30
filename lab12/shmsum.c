#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>


int main ()
{
        key_t key;
        int shmid;
        int *shmaddr;
        int *shmaddr1;
        int i, j;


        key = 100;
        shmid = shmget (key, sizeof(int), /*IPC_CREAT | 0666*/0);
        shmaddr = shmat (shmid, 0, 0);
        for (i = 0; i < 10; i++) {
                usleep (200000);
                for (j = 0; j < 10000000; j++)
                        (*shmaddr)++;
        }


        printf ("*shmaddr = %d\n", *shmaddr);
}