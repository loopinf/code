#include <stdio.h>

int global();
int main(void){
  static int i = 100;
  return 0;
}