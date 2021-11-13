// headers added for ease of testing solution.
#include <stdlib.h>
#include <memory.h>

unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k);

unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k) {
  #define STACKSIZE 0xfffffff
  void *ptr = (char *) malloc(STACKSIZE) + STACKSIZE;
  char offset[(size_t) &ptr - (size_t) ptr];
  unsigned long long result = BadF(n,p,k);
  return result;
}
