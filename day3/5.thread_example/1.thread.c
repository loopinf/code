#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 

void* thread_routine(void *arg){  
  printf("\n\nth func - tid:%lx\n", pthread_self());   
  for(;;){}
} 

int main(){    
//Q-- 쓰레드를 2개를 생성해주세요.





  printf("\n\ntid:%lx\n",pthread_self());  
  for(;;){}
}
