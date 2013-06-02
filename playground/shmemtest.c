#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char *argv[])
{
	key_t shmem_key;
	int shmem_id, rc;
	char *shmem_addr;
	struct shmid_ds shmid_ds_buf;

	shmem_key = ftok("hello", 1);

	shmem_id = shmget(shmem_key, 1 << 12, IPC_CREAT | 0666);
	if (shmem_id < 0)
		perror("shmget");

	printf("%d %d\n", shmem_key, 1 << 12);

	errno = 0;
	shmem_addr = shmat(shmem_id, NULL, 0);
	if (errno) {
		perror("shmat");
		goto out_destroy;
	}

	rc = fork();
	if (rc < 0) {
		perror("fork");
		goto out_destroy;
	} else if (rc > 0) {
		/* Parent */
		strcpy(shmem_addr, "hejsan");
		wait(&rc);
	} else {
		/* Child */
		sleep(2);
		printf("%s\n", shmem_addr);
		exit(EXIT_SUCCESS);
	}

out_destroy:
	if (shmctl(shmem_id, IPC_RMID, &shmid_ds_buf))
		perror("shmctl IPC_RMID");

}
