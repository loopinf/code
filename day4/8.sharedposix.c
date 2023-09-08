#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

struct mydata {
	int pid;
	int counter;
};

#define SHM_NAME	"/myshm"

static int view(void)
{
  int fd;
	int n;
	struct mydata local;
	struct mydata *info;

	fd = shm_open(SHM_NAME, O_RDWR|O_CREAT, 0644);
	if (fd == -1) {
		perror("shm_open()");
		return -1;
	}

	if (ftruncate(fd, sizeof(struct mydata)) == -1) {
		perror("ftruncate()");
		close(fd);
		return -1;
	}

	info = mmap(NULL, sizeof(struct mydata), 
			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (info == MAP_FAILED) {
		perror("mmap()");
		close(fd);
		return -1;
	}
	memset(info, 0, sizeof(struct mydata));

	close(fd);

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
	munmap(info, sizeof(struct mydata));

	return 0;
}

static int set(void)
{
	int fd;
	struct mydata *info;

	fd = shm_open(SHM_NAME, O_RDWR, 0644);
	if (fd == -1) {
		perror("shm_open()");
		return -1;
	}

	info = mmap(NULL, sizeof(struct mydata), 
			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (info == MAP_FAILED) {
		perror("mmap()");
		close(fd);
		return -1;
	}

	close(fd);

	info->pid = getpid();
	info->counter++;

	munmap(info, sizeof(struct mydata));

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