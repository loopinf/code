#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

void *sched_fn(void *nid)
{
  int nmyid = (size_t)nid;
  sleep(1);
  
  int policy;
  struct sched_param param;
  pthread_getschedparam(pthread_self(),&policy,&param);
    
  switch(policy) {
    case SCHED_OTHER:
      printf("SCHED_OTHER %d\n", nmyid);
      break;
    case SCHED_RR:
      sleep(1);
      printf("SCHED_RR %d\n", nmyid);
      break;
    case SCHED_FIFO:
      sleep(1);
      printf("SCHED_FIFO %d\n", nmyid);
      break;
  }
  printf("START TID=%d\n", nmyid);
  int num = 0;
  for( size_t i=0; i<100000; i++ )
  {
    for( size_t j=0; j<10000; j++ ) {
      num++;
      num--;
    }
  }
  printf("Pthread %d exit\n", nmyid);
  pthread_exit(NULL);
}

int main(int argc, char **argv) {
    unsigned int i = getuid();
    if(i==0)
      printf("The current user is root\n");
    else
      printf("The current user is not root\n");

    fprintf( stdout, "%s, %s, %s\n", argv[1], argv[2], argv[3] );

    pthread_t ppid1, ppid2, ppid3;
    pthread_attr_t attr1, attr2, attr3;

    struct sched_param param;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);
    // argv[1] == 0 SCHED_RR, 1 SCHED_FIFO, 2 SCHED_OTHER
    // argv[2] th1 pri, argv[3] th2 pri
    switch(atoi(argv[1])) {
    case 0:
      pthread_attr_setschedpolicy(&attr1,SCHED_RR);
      pthread_attr_setschedpolicy(&attr2,SCHED_RR);
      break;
    case 1:
      pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
      pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
      break;
    case 2:
      //SCHED_OTHER
      break;
    }

    param.sched_priority = atoi(argv[2]);
    pthread_attr_setschedparam(&attr1,&param);
    pthread_attr_setinheritsched(&attr1,  PTHREAD_EXPLICIT_SCHED);
    param.sched_priority = atoi(argv[3]);
    pthread_attr_setschedparam(&attr2,&param);
    pthread_attr_setinheritsched(&attr2,  PTHREAD_EXPLICIT_SCHED);
    
    int create3 = pthread_create( &ppid3, &attr3, sched_fn, (void *) 3);
    int create2 = pthread_create( &ppid2, &attr2, sched_fn, (void *) 2 );
    int create1 = pthread_create( &ppid1, &attr1, sched_fn, (void *) 1 );

    pthread_join(ppid3,NULL);
    pthread_join(ppid2,NULL);
    pthread_join(ppid1,NULL);
    pthread_attr_destroy(&attr3);
    pthread_attr_destroy(&attr2);
    pthread_attr_destroy(&attr1);

    return 0;
}


