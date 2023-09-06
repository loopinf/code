//1.mysignalhandler.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sigint_handler(int signo)
{
  printf("recv SIGINT!\n");
  psignal(signo, "Received signal");
  sleep(4);
  printf("done\n");
}
int main(void)
{
  printf("my pid %d\n", getpid());
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    perror("Cannot handle SIGINT!\n");
    _exit(0);
  }
  for (;;) pause(); // pause(2) : waiting a signal (any signal)
  return 0;
} 