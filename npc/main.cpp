#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
int i = 0;
	while (i<4) {
  int a = rand() & 1;
  int b = rand() & 1;
  top->a = a;
  top->b = b;
  top->eval();
  printf("a = %d, b = %d, f = %d\n", a, b, top->f);
  assert(top->f == (a ^ b));
  i++;
}
return 0;
}
