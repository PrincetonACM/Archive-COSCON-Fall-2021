#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE (1 << 28)
#define STACK_PAD 128

unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k);

void StackOverflowException(unsigned long long n, unsigned long long p, unsigned long long k) {
  printf("StackOverflow %llu %llu %llu\n", n, p, k);
}

unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k) {
  return n == 0 ? 0 : BadF(n - 1, p, k) + 17;
}

int main(void)
{
  unsigned long long caseA = 10,
                caseB = 222,
                caseC = 1000001,
                caseD = 1008001,
                caseE = 2000002,
                caseF = 1008111,
                caseG = 1007121;
  unsigned long long ResultA = BadFHandler(caseA, 0, 13), 
                ResultB = BadFHandler(caseB, 1, 222),
                ResultC = BadFHandler(caseC, 0, 0),
                ResultD = BadFHandler(caseD, 1, 1),
                ResultE = BadFHandler(caseE, 222, 222),
                ResultF = BadFHandler(caseF, 0, 0),
                ResultG = BadFHandler(caseG, 0, 0);
  printf("%llu : %llu\n", caseA, ResultA);
  printf("%llu : %llu\n", caseB, ResultB);
  printf("%llu : %llu\n", caseC, ResultC);
  printf("%llu : %llu\n", caseD, ResultD);
  printf("%llu : %llu\n", caseE, ResultE);
  printf("%llu : %llu\n", caseF, ResultF);
  printf("%llu : %llu\n", caseG, ResultG);

  return 0;
}
