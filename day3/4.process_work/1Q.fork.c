#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>
static long long num = 0;
int main(void)
{  
  printf("start\n");

  struct tms buf;
  clock_t ct, t1, t2;
  
  ct = sysconf(_SC_CLK_TCK);
  t1 = times(&buf);

//Q--
//Q--두 프로세스로 아래 연산을 수행하도록 코드 수정해주세요
//Q--절반씩 동시 작업이 되도록 코드를 변경해주세요

  int forked_pid = fork(); // pid == 0 child process
  long long start_idx = 1;
  long long end_idx = 2500000000;
  if (forked_pid == 0) {
    start_idx = 250000000;
    end_idx = 5000000000;
  }

  for (long long i = start_idx; i < end_idx; i++)
    {
      num += 1;
    }
  
  // for (long long i = 1; i < 5000000000; i++)
  // {
  //   num += 1;
  // }

  t2 = times(&buf);

  printf("num = %lld\n", num);
  
  printf("clock: %ld\n", ct);
  printf("t1: %ld\n", t1);
  printf("t2: %ld\n", t2);
  printf("utime : %ld\n", buf.tms_utime);
  printf("stime : %ld\n", buf.tms_stime);
  printf("Real time : %.1f sec\n", (double)(t2 - t1) / ct);
  printf("User time : %.1f sec\n", (double)buf.tms_utime / ct);
  printf("System time : %.1f sec\n", (double)buf.tms_stime / ct);
  printf("cutime : %.1f sec\n", (double)buf.tms_cutime / ct);
  printf("cstime : %.1f sec\n", (double)buf.tms_cstime / ct);

  wait(NULL);
  return 0;
} 