#include <stdio.h>
#include <signal.h> 
#include <unistd.h>  

int main(){
  
  int n_cp_pid = 0;
  int n_rm_pid = 0;
  // 시그널을 보내고자 하는 CP용 PID
  printf("Enter cp.c PID : ");
  scanf(" %d", &n_cp_pid);
  // 시그널을 보내고자 하는 RM용 PID
  printf("Enter rm.c PID : ");
  scanf(" %d", &n_rm_pid);
  
  int n_action = 0;
  while(1) {  
    printf("1: call do cp, 2 call alive cp, 3: call do rm, 4: call alive rm, 5: exit\naction=>");
    scanf(" %d", &n_action);
    printf("\n");
    
    switch(n_action) {
      case 1:
        kill(n_cp_pid, SIGUSR1);
        break;
      case 2:
        kill(n_cp_pid, SIGUSR2);
        break;
      case 3:
        kill(n_rm_pid, SIGUSR1);
        break;
      case 4:
        kill(n_rm_pid, SIGUSR2);
        break;
      case 5:
        kill(n_cp_pid, SIGTERM);
        kill(n_rm_pid, SIGTERM);
        kill(0, SIGTERM); // 자신에게도 종료 시그널을 전송
        break;
    }
  }  
  return 0;
}
