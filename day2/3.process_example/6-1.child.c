#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
  int n_count = 0;
  while(1) {
    printf("child.c %d\n", n_count);
    n_count++;
    sleep(1);

    if(n_count > 10) {
      return 2;
    }
  }
  return 0;
}
