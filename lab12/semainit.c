#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>


int main ()
{
        sem_t *sem;
        int svalue;
        int ival;


        printf ("Enter the initial value : ");
        scanf ("%d", &ival);
        sem = sem_open("testsem", O_CREAT, 0666, ival);
        sem_getvalue (sem, &svalue);
        printf ("svalue = %d\n", svalue);
}