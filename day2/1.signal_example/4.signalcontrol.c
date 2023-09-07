#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void handler_signal(int _signo) {
  printf("Received signal : %s(%d)\n", strsignal(_signo), _signo);
}
int main(void) {
  printf("%ld\n", sizeof(unsigned long int));
  printf("%ld\n", sizeof(sigset_t));
  sigset_t new;
  printf("%ld\n", sizeof(new.__val));
  signal(SIGINT, handler_signal);
  signal(SIGQUIT, handler_signal);
  signal(SIGTSTP, handler_signal);
  sigemptyset(&new);

  printf("mask : %ld\n", new.__val[0]);
  printf("mask : %ld\n", new.__val[1]);
  printf("mask : %ld\n", new.__val[2]);
  printf("mask : %ld\n", new.__val[3]);

  //비트-마스크 값 확인용 예시
  sigaddset(&new, SIGINT);
  printf("mask1 : %ld\n", new.__val[0]);
  sigaddset(&new, SIGQUIT);
  printf("mask2 : %ld\n", new.__val[0]);
  sigaddset(&new, SIGTSTP);
  printf("mask : %ld\n", new.__val[0]);

  printf("mask : %ld\n", new.__val[0]);
  printf("mask : %ld\n", new.__val[1]);
  printf("mask : %ld\n", new.__val[2]);
  printf("mask : %ld\n", new.__val[3]);

  printf("5sec Blocking signals\n");
  sigset_t old;
  sigprocmask(SIG_BLOCK, &new, &old); // new에 1에 해당하는 시그널을 block으로 mask 값 지정, 3번째 인수는 기 사용 중인 mask를 가져옴
  //sigprocmask(SIG_SETMASK, &old, 0); // 기존 마스크값으로 마스크 대체
  sleep(5);
  printf("UnBlocking signals, get pending\n");
  sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL); // new에 1에 해당하는 시그널을 unblock으로 mask 값 지정
  printf("5sec sleep\n");
  sleep(5);
  return 0;
}
