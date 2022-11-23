#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main ()
{
	int shmid;
	char buf[100];
	char *shmaddr;
	key_t key = 0x4d2;

	shmid = shmget (key, 100, IPC_CREAT | 0666);
	printf ("shmid = %d \n", shmid);

	shmaddr = shmat (shmid, NULL, 0);
	printf ("shmaddr = %p \n", shmaddr);
	strcpy (buf, shmaddr);
	printf ("buf = [%s]\n", buf);
	shmdt (shmaddr);
}