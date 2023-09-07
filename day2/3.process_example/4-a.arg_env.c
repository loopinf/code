#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
  int i;
  /* 모든 명령줄 인수 출력 */
  for (i = 0; i < argc; i++)
    printf("argv[%d]: %s \n", i, argv[i]);

  char **ptr;
  extern char **environ;
  /* 모든 환경 변수 값 출력*/
  for (ptr = environ; *ptr != 0; ptr++)
    printf("%s \n", *ptr);

  exit(0);
}

