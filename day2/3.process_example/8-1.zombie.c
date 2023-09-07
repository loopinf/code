#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <errno.h>

int main() {    
  pid_t childPid;    
  printf("\n\n");
  childPid = fork();    
  if(childPid > 0) {  // 부모 프로세스
    printf("\r\nPPID : %d, Child pid : %d\n",getpid(), childPid);
    sleep(10);    // 자식은 1초 이후 종료하기 때문에 9초간 좀비로 남아 있음
    printf("Parent Wakeup\n");
    wait(NULL);   // 자식 종료 완료 처리
    printf("1st wait done\n");
    if(wait(NULL) == -1) {
      perror(strerror(errno));
    };   // 자식 종료 대기 (기다릴 자식이 없으므로 에러)
    sleep(10);
    printf("Parent Done\n");
    exit(0);
  }
  else if(childPid == 0){  // 자식 코드
    printf("\r\nChild PID : %d\n", getpid());
    sleep(1);    
    printf("Child Done\n");
    exit(0);
  }
  else {  // fork 실패
    perror("fork Fail! \n");
    return -1;
  }
  return 0;
}
