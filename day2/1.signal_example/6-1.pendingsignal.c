#include <stdio.h>
#include <signal.h> 
#include <unistd.h>  

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

  // pending 마스크를 가져와서 어떤 signal이 pending 중인지 확인하고 의도된 처리를 하기 위해 사용
  // pending 마스크값 가져오기
  if(sigpending(&pendingset)==0){
    printf("\n\n Pending SIGNAL\n");
    // pending 마스크값에서 지정한 시그널(SIGQUIT) 있는지 확인
    if(sigismember(&pendingset,SIGQUIT)) {
      printf("SIGQUIT\n");
    }
    if(sigismember(&pendingset,SIGINT)){
      printf("SIGINT\n");
    }
    if(sigismember(&pendingset,SIGTSTP)){
      printf("SIGTSTP\n");
    }
  }
  else {
    printf("SIGQUIT / SIGINT / SIGTSTP signal not found\n");
  }

  sleep(3);
  sigprocmask(SIG_UNBLOCK,&set,NULL);
  printf("DONE\n");
  return 0;
}
