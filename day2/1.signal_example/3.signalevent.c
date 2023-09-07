#include <unistd.h>
#include <signal.h>
#include <stdio.h>
int n_input_counter = 0;
int n_add_result = 0;

void display(int _sig)
{
  printf("\n[RESULT]\n");
  printf("Count : %d, Result : %d\n", n_input_counter, n_add_result);
  alarm(5); // 5초 후 sigalrm 시그널 발생 등록 (매번 이 핸들러에서 5초 후 호출이 지정됨)
}
int main(void)
{
  signal(SIGALRM, display);
  signal(SIGTSTP, display);
  alarm(5); // 5초 후 sigalrm 시그널 발생 등록
  int n_value = 0;
  while (1) {
    printf("Enter number : ");
    scanf(" %d", &n_value);       // scanf로 인한 대기 상태이더라도 시그널 처리를 수행함
    n_input_counter++;
    n_add_result += n_value;
  }
}
