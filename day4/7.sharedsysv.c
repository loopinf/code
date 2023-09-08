#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/procfs.h>


#define ROUNDUP(x)	(((x) + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1))

struct mydata {
	int pid;
	int counter;
};

static int view(void)
{
	int n;
	key_t key = 7785;
	size_t size;
	int shmid;
	struct mydata local;
	struct mydata *info;

	size = ROUNDUP(sizeof(struct mydata));
	shmid = shmget(key, size, IPC_CREAT | 0644);
	if (shmid == -1) {
		perror("shmget()");
		return -1;
	}

	info = shmat(shmid, NULL, 0);
	if (info == (void *)-1) {
		perror("shmat()");
		return -1;
	}
	//memset(info, 0, sizeof(struct mydata)); <-- 기동시 늘 초기화 (고민해서 써야함)

	/* view */
	memset(&local, 0, sizeof(local));
	n = 0;
	while (1) {
		if (memcmp(info, &local, sizeof(struct mydata))) {
			/* diff */
			printf("pid = %d, counter = %d\n",
					info->pid, info->counter);
			memcpy(&local, info, sizeof(struct mydata));
			n++;

			if (n == 5) break;
		}
		sleep(1);
	}
	shmdt(info);

	return 0;
}

static int set(void)
{
	key_t key = 7785;
	size_t size;
	int shmid;
	struct mydata *info;

	size = ROUNDUP(sizeof(struct mydata));
	shmid = shmget(key, size, 0644);
	if (shmid == -1) {
		perror("shmget()");
		return -1;
	}

	info = shmat(shmid, NULL, 0);
	if (info == (void *)-1) {
		perror("shmat()");
		return -1;
	}

	info->pid = getpid();
	info->counter++;

	shmdt(info);

	return 0;
}

int main(int argc, char **argv)
{
	int viewmode = 0;

	if (argc == 2) {
		if (!strcmp(argv[1], "view")) {
			viewmode = 1;
		} else {
      perror("only arg view");
			return -1;
		}
	} 

	if (viewmode) {
		view();
	} else {
		set();
	}
	return 0;
}
