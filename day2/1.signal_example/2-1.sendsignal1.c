#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int argc,char *argv[]){
  int recv_pid = atoi(argv[1]);
  int ret;
  ret = kill(recv_pid, 0);    // 시그널을 보내지 않고 대상에 보낼 수 있는 권한이 있는지 확인
  printf("ret = %d\n", ret);
} 
