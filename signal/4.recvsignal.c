//4.signal_recver.c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sigint_handler(int signo)
{
  printf("recved signal - %d pid(#%d)", signo, getpid());
  psignal(signo, "Received signal");
}
int main(void)
{
  signal(SIGINT, sigint_handler);
  signal(SIGQUIT, sigint_handler);
  fork();
  printf("recver pid %d\n", getpid());
  while(1) {
    sleep(1);
  }
  return 0;
} 