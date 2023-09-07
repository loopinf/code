#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>    
#include <sys/wait.h>
#include <sys/wait.h>

void sigchildHandler(int sig, siginfo_t *info, void *ucontext) {
  printf("sender=%d, utime:%ld, stime:%ld\n", info->si_pid, info->si_utime, info->si_utime);
  psiginfo(info, "INFO");
    
  int n_status = 0; 
  int n_pid = waitpid(-1, &n_status, WNOHANG);  
  if (n_pid < 0) {
      perror("waitpid failed");
  } else if (n_pid == 0) {
      //정상
  } else if (WIFEXITED(n_status)) {
      printf("child TERMINATED return value(%d)\n", WEXITSTATUS(n_status));
  } else if (WIFSIGNALED(n_status)) {
      printf("child TERMINATED signal %d exit\n", WTERMSIG(n_status));
  } else if (WIFSTOPPED(n_status)) {
      printf("child SUSPENDED signal %d stop\n", WSTOPSIG(n_status));
  } else if (WIFCONTINUED(n_status)) {
      printf("child RUNNING\n");
  } 
}

// wait4(pid_t pid, int *status, int options, struct rusage *rusage);
// struct rusage {
// struct timeval ru_utime; /* user CPU time used */
// struct timeval ru_stime; /* system CPU time used */
// long ru_maxrss; /* maximum resident set size */
// long ru_ixrss; /* integral shared memory size */
// long ru_idrss; /* integral unshared data size */
// long ru_isrss; /* integral unshared stack size */
// long ru_minflt; /* page reclaims (soft page faults) */
// long ru_majflt; /* page faults (hard page faults) */
// long ru_nswap; /* swaps */
// long ru_inblock; /* block input operations */
// long ru_oublock; /* block output operations */
// long ru_msgsnd; /* IPC messages sent */
// long ru_msgrcv; /* IPC messages received */
// long ru_nsignals; /* signals received */
// long ru_nvcsw; /* voluntary context switches */
// long ru_nivcsw; /* involuntary context switches */
// };

int main(void) {  
  struct sigaction my_sig_action;
  my_sig_action.sa_flags = SA_SIGINFO;
  my_sig_action.sa_sigaction = sigchildHandler;
  sigaction(SIGCHLD, &my_sig_action, 0); // SIGCHILD - wait procedure

  int n_count = 0;
  printf("ready\n");
  int pid1 = fork();
  int pid2;
  if(pid1 != 0) {
    pid2 = fork();
    if(pid2 == 0){
      pid1 = 0;
    }
  }
  while(1) {
    sleep(1); 
    n_count++;

    if(pid1 <= 0) { continue; }
    printf("==============parent do %d\n", getpid());
    if(n_count == 5) {
      printf("==============kill \n");
      kill(pid1, SIGSTOP); 
      kill(pid2, SIGSTOP); 
      printf("==============all stop\n");
    }
    else if(n_count == 10) {
      kill(pid1, SIGCONT); 
      kill(pid2, SIGCONT); 
      printf("============all cont\n");
    }
  }
  return 0;
}