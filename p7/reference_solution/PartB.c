#define STACK_SIZE (1 << 26)
#define SEGV_STACK_SIZE (1<<20)

// headers added for ease of testing solution.
#include <stdlib.h>
#include <memory.h>
#include <setjmp.h>
#include <signal.h>

static char RECOVERY_STACK[1<<20];
static jmp_buf RecoveryContext;
static unsigned long long N, P, K;
stack_t segv_stack; struct sigaction sa;

void StackOverflowException(unsigned long long n, unsigned long long p, unsigned long long k);
unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k);

void HandleSIGSEGV(int signal, siginfo_t *si, void *arg) {
  longjmp(RecoveryContext, 1); // back to forward branch of if-statement in TestSO.
}

int TestSO(unsigned long long n, unsigned long long p, unsigned long long k) {
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask); 
    sa.sa_sigaction = HandleSIGSEGV; 
    sa.sa_flags   = SA_SIGINFO|SA_ONSTACK|SA_RESTART|SA_NODEFER;
    sigaction(SIGSEGV, &sa, NULL);

    memset(RECOVERY_STACK, 0, 1<<20);
    segv_stack.ss_sp = RECOVERY_STACK;
    segv_stack.ss_flags = 0;
    segv_stack.ss_size = SEGV_STACK_SIZE;
    sigaltstack(&segv_stack, NULL);

    if (!setjmp(RecoveryContext)) {
      // first time, execute BadF
      unsigned long long r = BadF(n,p,k);
      return r; // Will return if no overflow occurred
    } 
    else {
      StackOverflowException(N,P,K);
      return 0;
    }
}

unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k) {
  // For Part B	
    size_t b;
  	N = n; P = p; K = k;
  	unsigned long long t = TestSO(n, p, k);
  	return t;
}
