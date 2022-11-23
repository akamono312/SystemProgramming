#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main ()
{
	int shmid;
	char buf[100];
	char *shmaddr;
	key_t key = 1234;

	shmid = shmget (key, 100, IPC_CREAT | 0666);
	printf ("shmid = %d \n", shmid);

	shmaddr = shmat (shmid, NULL, 0);
	printf ("shmaddr = %p \n", shmaddr);
	printf ("Enter a string to write: ");
	gets (buf);
	strcpy (shmaddr, buf);
	shmdt (shmaddr);
}