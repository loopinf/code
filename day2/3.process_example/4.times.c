#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// 해당 실행파일 사용법
// ./4times u user cpu time
// ./4times e system cpu time
// ./4times i i/o proc

// times(&tms) 프로세스의 수행시간을 구하는 함수
// 구조체 tms
// times(): return clock_t (현재클럭틱, 프로세스 시작기준은 아님, 전역값)
// 인수로 전달한 포인터에 cpu 사용 시간이 기록됨
//clock_t tms_utime; //USER CPU time
//clock_t tms_stime; //SYSTEM CPU time
//clock_t tms_cutime; // 종료완료된 자식 프로세스들의 사용시간 합
//clock_t tms_cstime; // 종료완료된 자식 프로세스들의 사용시간 합

int main(int argc, char* argv[]) {
  int i;
  struct tms buf;
  clock_t ct, t1, t2;

  ct = sysconf(_SC_CLK_TCK); // 시스템 클럭 틱 100
  printf("Clock tick : %ld\n", ct);

  if ((t1 = times(&buf)) == -1) {  // 이시점에 cpu 동작시간이 기록, return 시간
    perror("times 1");
    exit(1);
  }
  
  if(argv[1][0] == 'i') {
    for (i = 0; i < 9999999; i++) {
      putchar('+');
    }  
    printf("\rcmd i\n");
  }
  else if(argv[1][0] == 'u') {
    for (i = 0; i < 99999999; i++) {
      i+=1;
      i-=1;
    }  
    printf("\rcmd u\n");
  }
  else {// fork 생성수 사용 유의
      for (i = 0; i < 9999; i++) {
      int i = fork();
      if(i == 0) {
        return 0;
      }       
    }  
    printf("cmd else\n");    
  }
  putchar('\n');

  if ((t2 = times(&buf)) == -1) { // 프로세스가 켜진 이후의 시간
    perror("times 2");
    exit(1);
  }

  printf("t1: %ld\n", t1);
  printf("t2: %ld\n", t2);
  printf("utime : %ld\n", buf.tms_utime);
  printf("stime : %ld\n", buf.tms_stime);
  printf("Real time : %.1f sec\n", (double)(t2 - t1) / ct);
  printf("User time : %.1f sec\n", (double)buf.tms_utime / ct);
  printf("System time : %.1f sec\n", (double)buf.tms_stime / ct);
  printf("cutime : %.1f sec\n", (double)buf.tms_cutime / ct);
  printf("cstime : %.1f sec\n", (double)buf.tms_cstime / ct);
}

