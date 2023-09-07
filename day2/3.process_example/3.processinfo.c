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
    sleep(2);
    printf("\n====CHILD INFO.");
  
  }
  else {
    printf("PARENT INFO.");
    if(setpgid(forkpid, forkpid) != 0) {
      // pid : 프로세스 그룹에 속한 프로세스의 ID, pgid : 새로 지정할 PGID
      // 자식을 새로운 그룹 리더로 변경
    }
  }

  printf("PID : %d\n", (int)getpid());
  printf("PPID : %d\n", (int)getppid());
  printf("PGRP : %d\n", (int)getpgrp());
  printf("PGID(0) : %d\n", (int)getpgid(0));                    // 자신이 속한 프로세스 그룹의 id를 리턴
  int n_my_pid = (int)getpid();
  printf("PGID(ME) : %d\n", (int)getpgid(n_my_pid));  // 해당 PID의 프로세스 그룹 id 리턴
  printf("PGID(1) : %d\n", (int)getpgid(1));                    // 1 PID의 프로세스 그룹 id 리턴
  printf("SID : %d\n", (int)getsid(0));                         // 자신이 속한 SID 리턴

   if(forkpid != 0) {
      // 부모프로세스는 자식 프로세스 종료시 까지 대기
      int exitchild_pid = wait(NULL);
      printf("exit PID : %d\n", exitchild_pid);
      wait(NULL);
   }
  else {
      if(setpgid(getpid(), getppid()) != 0) {
        // 다시 부모프로세스로 복귀
      }
      printf("go to parent group : PGID(0) : %d\n", (int)getpgid(0));  

      // (두 프로세스 그룹은 같은 세션의 속해있어야함) 만약 다르다면 실패
      if(setpgid(getpid(), 2268) != 0) {
        printf("failed setpgid[%s]\n", strerror(errno)); // 이동 실패 
      }   
   }
}

