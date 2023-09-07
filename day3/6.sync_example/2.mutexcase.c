#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
int ncount;    // 쓰레드간 공유되는 자원
int n_start = 0;

// 쓰레드 함수 1
void* do_loop(void *data){
  int i; 
  while(!n_start) { }
  for (i = 0; i < 100000; i++)    {        
    ncount++;   
    printf("loop1: %d\n", ncount);    
  }  
  return 0;  
}

// 쓰레드 함수 2
void* do_loop2(void *data){    
  int i;  
  while(!n_start) { }
  for (i = 0; i < 100000; i++)    {           
    ncount++;   
    printf("loop2: %d\n", ncount);     
  }    
  return 0;
}  
  
int main()
{    
  int thr_id;    
  pthread_t p_thread[2];    
  int status;    
  ncount = 0;    
  thr_id = pthread_create(&p_thread[0], NULL, do_loop, NULL);    
  printf("\ncreate t1 - %x\n", thr_id);    
  thr_id = pthread_create(&p_thread[1], NULL, do_loop2, NULL);  
  printf("\ncreate t2 - %x\n", thr_id);  
  for (int i = 0; i < 10000000; i++)    {}  // thread 생성 기다리기
  n_start = 1;
  pthread_join(p_thread[0], (void *) &status);    
  pthread_join(p_thread[1], (void *) &status);   
  printf("code  =  %d\n", status);   
  return 0;
}
