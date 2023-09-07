
#include <stdio.h>
#include <signal.h> 
#include <unistd.h>  
#include <string.h>  

int main(){
  sigset_t pendingset;
  sigset_t set;

  sigemptyset(&set);
  sigemptyset(&pendingset);

  sigaddset(&set,SIGQUIT);
  sigaddset(&set,SIGINT);
  sigaddset(&set,SIGTSTP);

  sigprocmask(SIG_BLOCK, &set, NULL);

  printf("SIGQUIT / SIGINT / SIGTSTP signal 입력\n");
  sleep(3);

  int n_pending_signo = 0;
  int n_pending_count = 0;
  // pending 상태인 시그널을 확인하여 개발자가 원하는 실행흐름으로 처리하고 싶을 때 사용
  // pending 마스크값 가져오기
  if(sigpending(&pendingset)==0){
    printf("\n\n Pending SIGNAL\n");
    // pending 마스크값에서 SIGQUIT가 있는지 확인
    if(sigismember(&pendingset,SIGQUIT)) {
      printf("SIGQUIT\n");
      n_pending_count++;
    }
    // pending 마스크값에서 SIGINT가 있는지 확인
    if(sigismember(&pendingset,SIGINT)){
      printf("SIGINT\n");
      n_pending_count++;
    }
    // pending 마스크값에서 SIGTSTP가 있는지 확인
    if(sigismember(&pendingset,SIGTSTP)){
      printf("SIGTSTP\n");
      n_pending_count++;
    }
    // n_pending_count는 SIGQUIT , SIGINT , SIGTSTP 중 몇개가 pending 상태 인지 확인
    for(int i = 0; i < n_pending_count; i++) {    
      sigwait(&pendingset,&n_pending_signo); // pending mask에서 하나씩 꺼내옴 (낮은 번호 부터)
      printf("CLEAR %s = %d\n", strsignal(n_pending_signo), n_pending_signo); // strsignel 시그널번호에 따른 정보 표시
    }
  }
  else {
    printf("SIGQUIT / SIGINT / SIGTSTP signal not found\n");
  }
  sigprocmask(SIG_UNBLOCK, &set, NULL); // 블럭 해제
  sleep(3);
  printf("DONE\n");
  return 0;
}
