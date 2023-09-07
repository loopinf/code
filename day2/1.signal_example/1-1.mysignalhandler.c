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
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {  // return이 SIG_ERR일 경우 해당 설정이 정상적으로 등록 되지 않음
    perror("Cannot handle SIGINT!\n");
    _exit(0);
  }
  for (;;) pause(); // pause(2) : waiting a signal (any signal)
  return 0;
} 
