#define _POSIX_C_SOURCE 200809L
#include <signal.h> 
#include <unistd.h> 
#include <stdio.h>  
#include <errno.h> 
#include <setjmp.h>

static jmp_buf jmpbuf;

void sigintHandlerAdv(int sig, siginfo_t *info, void *ucontext) {
  psignal(sig, "RECV:");
  printf("sender=%d, utime:%ld, stime:%ld\n", info->si_pid, info->si_utime, info->si_utime);
  psiginfo(info, "INFO");
  sleep(1);
  
  //goto RESET;
  longjmp(jmpbuf, 1); // setjmp(jmpbuf)로 설정된 위치로 이동
}

int main()
{
    sigset_t sigmask;
    sigfillset(&sigmask);
    struct sigaction my_sig_action;
    my_sig_action.sa_flags = SA_NODEFER | SA_SIGINFO;
    my_sig_action.sa_sigaction = sigintHandlerAdv;
    my_sig_action.sa_mask = sigmask;

	  // SIGSEGV 대해서 sig_int를 등록한다. 
    if (sigaction(SIGSEGV, &my_sig_action, 0) == -1)
    {
      perror("ERROR");
    } 

    //RESET: 
    int ret_jmp = 0;
    if((ret_jmp = setjmp(jmpbuf)) >= 1){    // setjmp를 이용해서 goto대신 사용(시그널핸들러에서는 goto를 이용할 수 없기때문에)
      switch(ret_jmp) {
        case 1: // long사용시 전달되는 두번째 인자값을 return값으로 수신
          // 에러 종료 처리
          printf("error segv handled\n");
          return 1;
          break;
        default:
          printf("unknown jump\n");
          return -1;
          break;
      }
    }else{
          printf("saved setjump\n");
    }

    int val1 = 10;
    int *pointer1 = (int*)0x335;
    printf("계산 val1=%d\n", val1);
    val1 += *pointer1;  // SIG_SEGV 발생하도록 연산 오류 코드
    printf("종료 val1=%d\n", val1);
}