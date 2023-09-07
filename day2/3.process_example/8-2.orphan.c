#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {    
  pid_t childPid;    
  printf("\n\n");
  childPid = fork();    
  if(childPid > 0) {  // 부모 프로세스
    printf("\r\nPPID : %d, Child pid : %d\n",getpid(), childPid);
    printf("Parent Done\n");
    exit(0);  // 자식의 종료보다 먼저 종료, 이시점 이후 자식이 1 pid 자식프로세스로 변경
  }
  else if(childPid == 0){  // 자식 코드
    printf("\r\nChild PID : %d\n", getpid());
    
    for(int i=0;i<10;i++) {
      printf("child pid: %d, PPID: %d\n", getpid(), getppid());
      sleep(1);
    }

    printf("Child Done\n");
    exit(0);
  }
  else {  // fork 실패
    perror("fork Fail! \n");
    return -1;
  }
  return 0;
}
