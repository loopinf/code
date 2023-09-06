//6.sendsignal3.c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void signalhandler1(int signo) {
  printf("\r recv Signal num = %d\n", signo);
  // 코드 작성 1 
  printf("\r signalhandler1 done\n");
}
void signalhandler2(int signo) {
  printf("\r recv Signal num = %d\n", signo);
  _exit(0);
  printf("\r signalhandler2 done\n");
}
int main(void) {
  // 코드 작성 2

  write(1, "wait 10s\n", 9);
  sleep(10);
  write(1, "done\n", 5);
  return 0;
}