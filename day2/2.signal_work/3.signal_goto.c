#define _POSIX_C_SOURCE 200809L 
#include <signal.h> 
#include <unistd.h> 
#include <stdio.h>  
#include <errno.h> 

void sigintHandlerAdv(int sig, siginfo_t *info, void *ucontext) {
  psignal(sig, "RECV:");
  printf("sender=%d, utime:%ld, stime:%ld\n", 
        info->si_pid, info->si_utime, info->si_stime);  // SIGCHLD 경우에만 utime / stime을 담아서 전송됨
  psiginfo(info, "INFO");
  sleep(1);
}

// utime stime확인을 위해 추가된 코드
void sigchildhander(int sig, siginfo_t *info, void *ucontext) {
  psignal(sig, "RECV CHILD:");
  printf("sender=%d, utime:%.1f sec, stime:%.1f sec\n", 
          info->si_pid, (double)info->si_utime / sysconf(_SC_CLK_TCK), (double)info->si_stime / sysconf(_SC_CLK_TCK));
  // info->si_utime -> _sifields._sigchld.si_utime
  psiginfo(info, "INFO");
}

int main()
{
    sigset_t sigmask;
    sigfillset(&sigmask);
    struct sigaction my_sig_action;
    my_sig_action.sa_flags = SA_NODEFER | SA_SIGINFO;
    my_sig_action.sa_sigaction = sigintHandlerAdv;
    my_sig_action.sa_mask = sigmask;

	  // SIGINT에 대해서 sig_int를 등록한다. 
    if (sigaction(SIGINT, &my_sig_action, 0) == -1)
    {
      perror("ERROR");
    } 

    //--> 시작: utime stime확인을 위해 추가된 코드
    my_sig_action.sa_sigaction = sigchildhander;
    my_sig_action.sa_mask = sigmask;
    if (sigaction(SIGCHLD, &my_sig_action, 0) == -1)
    {
      perror("ERROR");
    } 

    if(fork() == 0) {
      int j =0;
      printf("child do\n");  
      for(int i =0; i < 1000000000; i++) {
        j++;
        j--;
        j++;
        j--;
        j++;
        j--;
      }
      return 0;
    } // <-- 종료
    
    int fd[2];
    int ret_pipe = pipe(fd);
    printf("pipe ret = %d\n", ret_pipe);  
    while(1) {
      char readed[10] = { 0x00 };
      int ret_read = 0;      
      replay:
      ret_read = read(fd[0], readed, sizeof(readed)); // i/o대기 중 시그널 발생 시 i/o return값이 -1로 전달됨
      printf("read ret = %d, error no:%d\n", ret_read, errno);
      if(errno == EINTR) { // 위 상황의 경우 EINTR발생(해당에러는 보통 시스템 콜 수행중 인터럽트가 걸려 수행이 중단될 시 발생)
        goto replay; // replay로 goto
      }
    }
}