#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sighandler(int signo, siginfo_t *si, void* ucontext)
{
    if(si->si_code == SI_QUEUE)
    {
        printf("User RTS signal %d\n", si->si_pid);
        printf("Sig  Number %d\n",     si->si_signo);
        printf("User Data is %d\n",    si->si_value.sival_int);
        getchar();
    }
    else
    {
        printf("Get none realtime signal %d\n", signo); 
    }
}

int main()
{
    struct sigaction sigact;
    printf("My pid %d\n", getpid());
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags     = SA_SIGINFO;
    sigact.sa_sigaction = sighandler; 
    if (sigaction(SIGRTMIN, &sigact, 0) == 1)
    {
        printf("signal error\n");
        _exit(0);
    }   
    while(1)
    {
        sleep(1);
    }  
}
