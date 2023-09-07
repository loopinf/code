#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t first_mutex;  
pthread_mutex_t second_mutex;

void *function1( ) {
  pthread_mutex_lock(&first_mutex);  // to acquire the resource lock
  printf("T1 acquired first_mutex\n");
  sleep(1);
  pthread_mutex_lock(&second_mutex);
  printf("T1 acquired second_mutex\n");
  pthread_mutex_unlock(&second_mutex); // to release the resource
  printf("T1 released second_mutex\n");
  pthread_mutex_unlock(&first_mutex);
  printf("T1 released first_mutex\n");
  return NULL;
}
void *function2( ) {
  pthread_mutex_lock(&second_mutex);
  printf("T2 acquired second_mutex\n");
  sleep(1);
  pthread_mutex_lock(&first_mutex);
  printf("T2 acquired first_mutex\n");
  pthread_mutex_unlock(&first_mutex);
  printf("T2 released first_mutex\n");
  pthread_mutex_unlock(&second_mutex);
  printf("T2 released second_mutex\n");
  return NULL;
}

int main() {
  pthread_mutex_init(&first_mutex,NULL); 
  pthread_mutex_init(&second_mutex,NULL);
  pthread_t one, two;  
  pthread_create(&one, NULL, function1, NULL);  
  pthread_create(&two, NULL, function2, NULL);
  pthread_join(one, NULL);
  pthread_join(two, NULL);
  printf("END\n");
}
