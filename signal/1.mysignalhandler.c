#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sigint_handler(int signo)
{
  printf("recv SIGINT!\n");
  psignal(signo, "Received signal");
}
int main(void)
{
  printf("my pid %d\n", getpid());
  if (signal(SIGINT, sigint_handler) ==  SIG_ERR){
    perror("Cannot handle SIGINT!\n");
    _exit(0);
  }
  for (;;) pause();
  return 0;
}