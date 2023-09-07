
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void cleanup(void *arg) {
  printf("cleanup : %s\n", (char *)arg);
}

void * thr_fn1(void *arg) {
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);

  printf("thread 1 start\n");
  pthread_cleanup_push(cleanup, "thread 1 first handler");
  pthread_cleanup_push(cleanup, "thread 1 second handler");
  printf("thread 1 push complete\n");

  while(1) {
    
//-- 쓰레드가 받은 cancel 요청을 처리 하도록 추가해주세요

  }

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
  sleep(2);
  pthread_cancel(tid1);

  if(err != 0) {
    perror("thread err");
  }
  err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
  err = pthread_join(tid1, &thret);
  printf("thread 1 exit code %ld \n", (size_t)thret);
  
  err = pthread_join(tid2, &thret);
  printf("thread 2 exit code %ld\n", (size_t)thret);
  exit(0);
}
