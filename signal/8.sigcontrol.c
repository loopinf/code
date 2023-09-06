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
  sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL);
  sleep(5);
  printf("UnBlocking signals, get pending\n");
  sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);
  printf("5sec sleep\n");
  sleep(5);
  return 0;
}