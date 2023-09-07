#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// 쓰레드 함수

int n_counter = 0;
int n_do_counter = 0;
void *t_function(void *data)
{
  int id = 0;
  id = *((int *)data);
  //---Q 여기서 대기하다가 main코드의 작업시작시점 이후 thread들이 작업을 시작하도록 해주세요.

  while (1)
  {
    printf("%d : %d\n", id, n_counter);
    n_counter++;
    if (n_counter > 10000)
    {
      break;
    }
  }
  return NULL;
}

int main()
{
  pthread_t p_thread[2];
  int thr_id;
  int status;
  int a = 1;
  int b = 2;
  // 쓰레드 생성 시 인수 1 을 넘긴다.
  thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
  if (thr_id < 0)
  {
    perror("thread create error : ");
    exit(0);
  }

  // 쓰레드 생성 시 인수 2 를 넘긴다.
  thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
  if (thr_id < 0)
  {
    perror("thread create error : ");
    exit(0);
  }
  sleep(1);

  // Q-- 이시점에 모든 쓰레드가 작업을 시작하게해주세요. (쓰레드 작업시작)

  // 쓰레드 종료를 기다린다.
  pthread_join(p_thread[0], (void **)&status);
  pthread_join(p_thread[1], (void **)&status);
  return 0;
}
