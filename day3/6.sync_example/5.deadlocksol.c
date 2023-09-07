#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
 
pthread_mutex_t mutex; 
void* mutex_lock(void *data){ 
    sleep(1);
    pthread_mutex_lock(&mutex); 
    for(int i=0;i<5;i++){ 
        printf("pthread_mutex_lock :%d\n",i); 
        sleep(1); 
    } 
    pthread_mutex_unlock(&mutex); 
    return NULL;
}
void* mutex_try_lock(void *data){ 
    sleep(1);
    if(pthread_mutex_trylock(&mutex)==0){//NOT EBUSY 
        for(int i=0;i<5;i++){ 
            printf("pthread_mutex_trylock :%d\n",i); 
            sleep(1); 
        } 
        pthread_mutex_unlock(&mutex); 
    }else{ 
        printf("pthread_mutex_trylock failed!\n"); 
    } 
    return NULL; 
} 

void* mutex_timed_lock(void *data){ 
    sleep(1);
    struct timespec ts; 
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec+=4; 
    ts.tv_nsec=0; 
    
    if(pthread_mutex_timedlock(&mutex,&ts) == 0) {     
      for(int i=0;i<5;i++){ 
          printf("pthread_mutex_timedlock :%d\n",i); 
          sleep(1); 
      }
      pthread_mutex_unlock(&mutex);  
    }else{ 
        printf("pthread_mutex_timedlock failed!\n"); 
    } 
    return NULL;
}
 
int main(void){ 
    pthread_t pid[3]; 
    int thr_id; 
    int status; 
    pthread_mutex_init(&mutex, NULL);
    thr_id = pthread_create(&pid[1], NULL, mutex_try_lock, NULL); 
    if (thr_id < 0) 
    { 
        perror("thread create error : "); 
        exit(0); 
    }
    thr_id = pthread_create(&pid[2], NULL, mutex_timed_lock, NULL); 
    if (thr_id < 0) 
    { 
        perror("thread create error : "); 
        exit(0); 
    }
    thr_id = pthread_create(&pid[0], NULL, mutex_lock, NULL); 
    if (thr_id < 0) 
    { 
        perror("thread create error : "); 
        exit(0); 
    }
    pthread_join(pid[0], (void **)&status); 
    pthread_join(pid[1], (void **)&status); 
    pthread_join(pid[2], (void **)&status);
 
    return 0; 
} 
