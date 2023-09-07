#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int signo) {
  psignal(signo, "Received Signal:");
}

int main(void) {
  sigset_t set;
  signal(SIGALRM, handler);
  sigfillset(&set);
  sigdelset(&set, SIGALRM);
  alarm(3);
  printf("Wait...\n");
  sigsuspend(&set);   // 마스크로 지정한 시그널을 블록하고 0인 값의 시그널만 언블록 (비교 pause 모든 시그널 대기)
  printf("DONE...\n");
  return 0;
}
