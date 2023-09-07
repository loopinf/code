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
  if (signal(SIGINT, SIG_IGN) == SIG_ERR) {   // 해당 시그널을 무시하도록 설정
    perror("Cannot handle SIGINT!\n");
    _exit(0);
  }
  for (;;) pause(); // pause(2) : waiting a signal (any signal)
  return 0;
} 
