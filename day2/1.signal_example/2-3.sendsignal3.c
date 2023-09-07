#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void signalhandler1(int signo) {
  printf("\r recv Signal num = %d\n", signo);
  raise(SIGINT); // 시그널 핸들러 동작 중 다른 시그널 핸들러가 호출되도록 시그널 발생
  printf("\r signalhandler1 done\n");
}
void signalhandler2(int signo) {
  printf("\r recv Signal num = %d\n", signo);
  _exit(0); // system call 
  printf("\r signalhandler2 done\n");
}
int main(void) {
  signal(SIGALRM, signalhandler1);
  signal(SIGINT, signalhandler2);
  alarm(2);
  write(1, "wait 10s\n", 9);
  sleep(10);
  write(1, "done\n", 5);
  return 0;
}
