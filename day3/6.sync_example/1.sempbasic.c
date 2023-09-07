#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <stdint.h>
#include <unistd.h>

unsigned int total_count = 0;   // 카운트 전역변수

int n_start = 0;
void *func_sem(void *param)
{
  int thread_no = (size_t)param;
  while(n_start == 0) {
  }
  for (int i = 0; i < 10000; i++) {
    total_count = total_count + 1;
    printf("id:%d, value:%d\n", thread_no, total_count);
  }
  return 0;
}

int main()
{
// Q-- 세마포어를 사용해주세요

  pthread_t th[3];
  pthread_create(&th[0], NULL, func_sem, (void *)1);
  pthread_create(&th[1], NULL, func_sem, (void *)2);
  pthread_create(&th[2], NULL, func_sem, (void *)3);

  sleep(2);
  n_start = 1;
  for (int i = 0; i < 3; i++) {
      pthread_join(th[i], NULL);
  }  


  return 0;
}
