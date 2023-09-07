#define _POSIX_C_SOURCE 200809L 
#include <signal.h> 
#include <unistd.h> 
#include <stdio.h>  
#include <errno.h> 

void sigintHandler(int signo)
{
  psignal(signo, "RECV:");
  sleep(3);
  printf("end\n");
}

void sigintHandlerAdv(int sig, siginfo_t *info, void *ucontext) { // info SA_SIGINFO flag사용으로 추가 전달되는 인수
  psignal(sig, "RECV:");
  printf("sender=%d, utime:%ld, stime:%ld\n", info->si_pid, info->si_utime, info->si_utime);
  sleep(1);
  psiginfo(info, "INFO"); // 시그널 송신자 시그널 관련 정보 표시
}

int main()
{
    sigset_t sigmask;
    sigfillset(&sigmask); // 모든 시그널 마스크 1로 설정
    sigdelset(&sigmask, SIGINT); // <<- 연속으로 누르면 연속 처리하도록 블럭마스크에서 해제
                                 // SA_NODEFER 제거 시 시그널 핸들러를 호출한 시그널에 대해 핸들러 실행 중엔 블록됨
    struct sigaction my_sig_action;
    my_sig_action.sa_flags = SA_NODEFER | SA_SIGINFO; // 동작 관련 flag 등록
    my_sig_action.sa_sigaction = sigintHandlerAdv;
    my_sig_action.sa_mask = sigmask;  // 해당 시그널이 동작할때 블럭 마스크 등록

	// SIGINT에 대해서 sig_int를 등록한다. 
    if (sigaction(SIGINT, &my_sig_action, 0) == -1)
    {
      perror("ERROR");
    }   
    while(1) {
      pause();
    }
}