#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// 쓰레드 함수

int n_do_proc = 0;
void *t_function(void *data)
{    
  int id, i = 0;    
//Q-- id에 저장해주세요.
  while(1) {   
    printf("%d : %d\n", id, i);   
    i++; 
    if(i > 1000) { break; }
  }
  return NULL;
}

int main() {    
  pthread_t p_thread[2];    
   int thr_id;    
  int status;   
  int a = 1;    
  int b = 2;    
//Q-- 쓰레드1 생성 시 인수 a를 넘기는 코드를 작성해주세요.



//Q-- 쓰레드2 생성 시 인수 b를 넘기는 코드를 작성해주세요.



  sleep(1);
  n_do_proc = 1;
  // 쓰레드 종료를 기다린다.     
  pthread_join(p_thread[0], (void **)&status); 
  pthread_join(p_thread[1], (void **)&status);    
  return 0;
}
