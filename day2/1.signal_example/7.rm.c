#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sigusr1_handler(int _sig)
{
  printf("\ndo del\n");
  system("rm copy.txt\n");  // sigusr1 시그널 수신 시 입력한 쉴 명령어 실행 
} 
void sigusr2_handler(int _sig)
{
  printf("\nrm.c - alive\n"); // sigusr2 시그널 수신 시 입력한 쉴 명령어 실행 
}
int main(void)
{
  printf("my rm.c id: %d\n", getpid());
  signal(SIGUSR1, sigusr1_handler);
  signal(SIGUSR2, sigusr2_handler);
  printf("wait...\n");
  while (1) {
    pause();
  }
}
