#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

int pid = 0;
void exitChild(int _sig)
{
  printf("\nAlarm\n");
  kill(pid, SIGINT);
} 

int main(int argc, char *argv[]) { 
  pid = fork();
  if (pid== 0) { 
    /* child process */ 
    execl("6-1.child", "myproc", NULL);   // 자식프로세스는 다른 프로그램으로 대치
    printf("after execlp!\n");
  } else {      
     /* parent process */ 
    signal(SIGALRM, exitChild);           // 핸들러 등록
    alarm(5);   // <-- 11초 이상으로 설정하면 정상종료로 client 에서 동작하게 코드를 작성함
    printf("reg alarm\n");
    int status = 0;
    wait(&status);                        // 값 가져오기
    int exitnum = status >> 8;            // 정상적으로 종료된 경우의 수신 값
    int signalnum = status &= 0xFF;       // 시그널로 종료된 경우의 수신 값
    printf("Child Complete! ret: %d, signal:%d\n", exitnum, signalnum);
    exit(0);
  } 
}
