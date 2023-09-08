#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int fd[2];
	pid_t pid;
	char buf[1024];
	int childstatus;

	printf("[%d] start\n", getpid());
	memset(buf, 0, sizeof(buf));

  printf("fd[0] = %d\n", fd[0]);
	printf("fd[1] = %d\n", fd[1]);
	if (pipe(fd)) {
		perror("pipe()");
		return -1;
	}

  printf("after pipe: fd[0] = %d\n", fd[0]);
	printf("after pipe: fd[1] = %d\n", fd[1]);
	pid = fork();
	if (pid == 0) {
		/* child process */
		close(fd[1]);
		printf("in child fd[0] = %d\n", fd[0]);
		printf("in child fd[1] = %d\n", fd[1]);

    while(read(fd[0], buf, sizeof(buf)) > 0) {
		  printf("[%d] recv child : %s\n", getpid(), buf);
    }
    
		close(fd[0]);

	} else if (pid > 0) {
		/* parent process */
		close(fd[0]);
		
    printf("msg: ");
    fflush(stdout);
    while(read(0, buf, sizeof(buf)) > 0) {
      write(fd[1], buf, strlen(buf));
      sleep(1);
      printf("msg: ");
      fflush(stdout);
    }
		
		close(fd[1]);

		pid = wait(&childstatus);

	} else {
		/* error case */
		perror("fork()");
		goto err;
	}
	return 0;

err:
	close(fd[0]);
	close(fd[1]);
	return -1;
}
