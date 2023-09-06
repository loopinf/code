//7.signalevent.c
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
int n_input_counter = 0;
int n_add_result = 0;

// 적절한 곳에 코드를 추가하여
// 응용 5초마다 더하기한값을 화면에 출력해주세요.
// 또는 Ctrl+Z를 눌렀을 때 화면에 출력해주세요
//      -> 이때는 다시 그 시점부터 5초뒤어야합니다.

void display(int _sig)
{
  printf("\n[RESULT]\n");
  printf("Count : %d, Result : %d\n", n_input_counter, n_add_result);
  alarm(5);
}
int main(void)
{
  // signal(SIGALRM, display);
  // alarm(5);
  int n_value = 0;
  while (1) {
    printf("Enter number: ");
    scanf(" %d", &n_value);
    

    n_input_counter++;
    n_add_result += n_value;
  }
}