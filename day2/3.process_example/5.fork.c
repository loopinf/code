#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> // for execl(), fork() 
#include <wait.h>   // for wait()
int main(int argc, char *argv[]) { 
  int pid; 
  printf("in Parent1\n");
  pid = fork();
  printf("after fork()\n");
  if(pid < 0) { 
    fprintf(stderr,"Fork Failed");
    exit(-1);
  } else if (pid== 0) { 
    //char *vargs_err[] = {"./4.times.c", "1"}; // 배열에 NULL이 없으면 정상 실행되지 않음
    //char *vargs_ok[] = {"./4.times.c", NULL};
    //char *env[] = {"env1, env2", NULL};
    /* child process */ 
    // func1 execl
    //execl("/bin/ls", "ls", NULL); // 실행 가변인수로
    
    // func2 execv
    //execv("/bin/ls", vargs_ok); // 실행 배열전달

    // func3 execle
    //execle("4-a.arg_env", "test", NULL, env); // 임의의 환경변수 전달

    // func 4
    //execve("4-a.arg_env", vargs_ok, env); // 임의의 환경변수 전달

    // func 5
    //execl("ls", "ls", NULL); // <- 실행안됨
    execlp("ls", "ls", NULL); // <- 실행됨 (환경변수 PATH 참조)

    printf("after execl!\n");

  } else { 
    /* parent process */ 
    wait(NULL);
    printf("Child Complete!\n");
    exit(0);
  } 
}

// 정의된 함수 
//l 가변인수 (끝에 NULL포함)
//v 배열 전달
//p PATH 환경변수 안에 들어있는 경로를 이용해서 찾음
// e 환경변수 전달
// int execl(const char *pathname, const char *arg, .../* (char  *) NULL */);
// int execv(const char *pathname, char *const argv[]);
// int execle(const char *pathname, const char *arg, .../*, (char *) NULL, char *const envp[] */);
// int execve(const char* pathname, char *const argv[], char *const envp[]);
// int execlp(const char *file, const char *arg, .../* (char  *) NULL */);
// int execvp(const char *file, char *const argv[]);
// int execvpe(const char *file, char *const argv[],char *const envp[]);