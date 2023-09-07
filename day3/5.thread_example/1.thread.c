#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_routine(void *arg)
{
  printf("\n\nth func - tid:%lx\n", pthread_self());
  for (;;)
  {
  }
}

int main()
{
  // Q-- 쓰레드를 2개를 생성해주세요.
  pthread_t tid1;
  pthread_t tid2;
  pthread_create(&tid1, NULL, thread_routine, NULL);
  pthread_create(&tid2, NULL, thread_routine, NULL);

  pthread_join(tid1, NULL);

  printf("\n\ntid:%lx\n", pthread_self());
  for (;;)
  {
  }
}
