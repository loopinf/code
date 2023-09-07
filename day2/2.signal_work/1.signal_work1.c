#include <stdio.h>
#include <signal.h>
#include <unistd.h>
static int num = 0;
void sigintHandler(int _signo) {
  printf("called sigintHandler: %d\n", _signo);

  // 연산코드를 시그널 핸들러에 작성 (시그널을 수신할 때마다 연산 수행하도록 구성)
  for (int i = 1; i < 10; i++)
  {
    num += i;
  }
  printf("num = %d\n", num);
}
void alarmHandler(int _signo) {
  psignal(_signo, "Received signal");
  raise(SIGINT);  // 시그널 동작 중 다른 시그널 호출 이 라인에서 다른 시그널핸들러로 실행흐름 이동, 종료 후 다시 복귀
  printf("alarm end\n");
}
int main(void)
{  
  printf("start - mypid: %d\n", getpid());
  
  signal(SIGINT, sigintHandler);
  signal(SIGALRM, alarmHandler);
  alarm(5);
  
  while(1) {
    // 시그널 이벤트 핸들러 등록 후 대기
    pause();
  }
  return 0;
} 

// 5초 후 sigalarm 발생, 
// 해당 시그널에서 자신한테 또 시그널을 발생시켜 핸들러로 구성한 기능 코드 호출
// killall -SIGUSR1 3.waiting (3.waiting 이름의 프로세스 모두 에게 전송)