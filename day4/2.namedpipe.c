#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILENAME		"./mynamepipe"

static int writer(void)
{
	int fd;
	char buf[128];

	printf("namedpipe unlink fifo\n");
	unlink(FIFO_FILENAME);
  
  printf("namedpipe create fifo\n");
	if (mkfifo(FIFO_FILENAME, 0644)) {
		perror("mkfifo()");
		return -1;
	}

	printf("call open()\n");
	fd = open(FIFO_FILENAME, O_WRONLY);
	if (fd < 0) {
		perror("open()");
		return -1;
	}
  
  printf("msg: ");
  fflush(stdout);
  while(read(0, buf, sizeof(buf)) > 0) {
    write(fd, buf, strlen(buf));
    sleep(1);
    printf("msg: ");
    fflush(stdout);
  }

	close(fd);

	return 0;
}

static int reader(void)
{
	int fd;
	char buf[128];

	printf("namedpipe open()\n");
	fd = open(FIFO_FILENAME, O_RDONLY);
	if (fd < 0) {
		perror("open()");
		return -1;
	}

  while(read(fd, buf, sizeof(buf)) > 0) {
    printf("[%d] recv child : %s\n", getpid(), buf);
  }

	close(fd);

	return 0;
}

int main(int argc, char **argv)
{
  // 사용방법: ./2.namepipe w 또는 /2.namepipe r
	if (argc < 2) {
	  printf("%s w or r\n", argv[0]);
		return -1;
	}

	if (!strcmp(argv[1], "r")) {
		/* reader */
		reader();
	} else if (!strcmp(argv[1], "w")) {
		/* writer */
		writer();
	} else {
	  printf("command error (w or r)\n");
		return -1;
	}

	return 0;
}
