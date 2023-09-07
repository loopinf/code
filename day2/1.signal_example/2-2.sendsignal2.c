#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

int main(int argc,char *argv[]){  
  int targetPID = 0;
  while (1) {
    printf("Enter PID to kill : ");
    scanf("%d", &targetPID);
    if (kill(targetPID, SIGKILL) == -1) {   // 지정된 pid 프로세스에게 SIGKILL 전송
      switch (errno) {
        case EPERM: // 대상에게 전송할 권한 없음
          printf("EPERM!\n");
          break;
        case ESRCH: // 해당 프로세스 ID가 없음
          printf("NotFound %d\n", targetPID);
          break;
      }
    } else {
      printf("Send! -> %d\n", targetPID);
    }
  }
}
