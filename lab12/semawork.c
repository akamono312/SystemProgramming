#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>


int main ()
{
    sem_t *sem;
    int i, work_t;


    sem = sem_open ("testsem", O_CREAT, 0666, 1);
    srand (time(NULL));
    for (i = 0; i < 10; i++) {
        printf ("Trying to get a semaphore.... \n");
        sem_wait (sem);


        work_t = rand () % 5 + 1;
        printf ("Working for %d sec.\n", work_t);
        sleep (work_t);
        printf ("      Done. \n\n");


        sem_post (sem);
        sleep (1);
    }
}