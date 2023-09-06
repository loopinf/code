#include <stdio.h>
#include <unistd.h>
#include <signal.h>
static int num = 0;
void calc(int signo) {
  for (int i = 1; i < 10; i++)
  {
    num += i;
  }
  printf("num = %d\n", num);
}
void alarmhandler(int signo) {
  printf("alarm do\n");
  raise(SIGINT);
  printf("alarm done\n");
}

int main(void)
{  
  alarm(5);

  printf("start\n");
  // sigset_t new;

  signal(SIGINT, calc);
  signal(SIGALRM, alarmhandler);

  while(1) {
    pause();
  }

  return 0;
} 