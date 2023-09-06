//4.sendsignal1.c
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int argc,char *argv[]){
  // 일부 코드 작성  
  int shot_pid = atoi(argv[1]);
  int shot_signal = atoi(argv[2]);

  int ret;
  ret = kill(shot_pid, shot_signal);
  printf("ret = %d\n", ret);


} 