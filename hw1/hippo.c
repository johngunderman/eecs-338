#include <stdio.h>
#include <stdlib.h>


void
main (void) {
  
  int pid = getpid();

  printf("%d\n", pid);

  exit(0);
}
