a.case1_.c
#include <signal.h> 
#include <unistd.h> 
#include <stdio.h>  
#include <errno.h> 

void sigintHandlerAdv(int sig, siginfo_t *info, void *ucontext) {
  psignal(sig, "RECV:");
  printf("sender=%d, utime:%ld, stime:%ld\n", info->si_pid, info->si_utime, info->si_utime);
  psiginfo(info, "INFO");
  sleep(1);
}

int main()
{
    sigset_t sigmask;
    sigfillset(&sigmask);
    struct sigaction my_sig_action;
    my_sig_action.sa_flags = SA_SIGINFO;
    my_sig_action.sa_sigaction = sigintHandlerAdv;
    my_sig_action.sa_mask = sigmask;

    // SIGINT에 대해서 sig_int를 등록한다. 
    if (sigaction(SIGINT, &my_sig_action, 0) == -1)
    {
      perror("ERROR");
    } 

    int fd[2];
    int ret_pipe = pipe(fd);
    printf("pipe ret = %d\n", ret_pipe);  
    while(1) {
      char readed[10] = { 0x00 };
      int ret_read = read(fd[0], readed, sizeof(readed));
      printf("read ret = %d\n", ret_read);
    }
}