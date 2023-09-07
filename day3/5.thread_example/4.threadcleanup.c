#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void cleanup(void *arg) {
  printf("cleanup : %s\n", (char *)arg);
}

void * thr_fn1(void *arg) {
  printf("thread 1 start\n");
  pthread_cleanup_push(cleanup, "thread 1 first handler");
  pthread_cleanup_push(cleanup, "thread 1 second handler");
  printf("thread 1 push complete\n");

  if (arg) { return ((void *)1); }
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return ((void *)11);
}

void * thr_fn2(void *arg) {
  printf("thread 2 start \n");
  pthread_cleanup_push(cleanup, "thread 2 first handler");
  pthread_cleanup_push(cleanup, "thread 2 second handler");
  printf("thread 2 push complete\n");
  if (arg) { pthread_exit((void *)2); }

  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  pthread_exit((void *)22);
}

int main(void) {
  int err = 0;  
  pthread_t tid1, tid2;
  void *thret;
  err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
  if(err != 0) {
    perror("thread err");
  }
  err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);

//-- 쓰레드가 종료될때까지 기다리다가 return 값을 받아 화면에 출력해주세요






  exit(0);
}
