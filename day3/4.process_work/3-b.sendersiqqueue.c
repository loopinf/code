#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int agvc, char* argv[])
{
  union sigval value; 
  value.sival_int = atoi(argv[2]);
  sigqueue(atoi(argv[1]), SIGRTMIN, value); 
}
