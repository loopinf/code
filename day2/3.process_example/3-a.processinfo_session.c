#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <errno.h>
#include <string.h>

int main() {
  int forkpid = fork();
  if (forkpid == -1) {
      perror("fork");
      return -1;
  }
  else if(forkpid == 0) {
    // 부모가 먼저 수행되도록 2초 대기
    printf("\n====CHILD -> setsid\n");
    setsid(); // 이 이후에는 터미널 종료 및 제어범위에서 나감
    fork();
    sleep(30);    
  }
  else {
    // 부모프로세스는 자식프로세스 종료시 까지 대기
    int exitchild_pid = wait(NULL);
    printf("\n exit PID : %d", exitchild_pid);
    printf("\n===PARENT INFO.");
  }

  printf("PID : %d\n", (int)getpid());
  printf("PPID : %d\n", (int)getppid());
  printf("PGRP : %d\n", (int)getpgrp());
  printf("PGID(0) : %d\n", (int)getpgid(0));            // 자신이 속한 프로세스 그룹의 id를 리턴
  printf("SID : %d\n", (int)getsid(0));                 // 자신이 속한 SID 리턴
}

