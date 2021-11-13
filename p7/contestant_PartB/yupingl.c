#include <stdlib.h>
#include <memory.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>

unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k);
void StackOverflowException(unsigned long long n, unsigned long long p, unsigned long long k);

static jmp_buf buf;

void sigsegv_handler(int signum, siginfo_t *info, void *data) {
    // printf("handling signal %d. SIGSEGV = %d, SIGBUS = %d\n", signum, SIGSEGV, SIGBUS);
    siglongjmp(buf, 1);
}

unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k) {
    // signal(SIGSEGV, signalHandler);
    // signal(SIGBUS, signalHandler);
    struct sigaction action;
    bzero(&action, sizeof(action));
    action.sa_flags = SA_SIGINFO|SA_STACK;
    action.sa_sigaction = &sigsegv_handler;
    sigaction(SIGSEGV, &action, NULL);

    int SEGV_STACK_SIZE = 1000000;
    stack_t segv_stack;
    segv_stack.ss_sp = valloc(SEGV_STACK_SIZE);
    segv_stack.ss_flags = 0;
    segv_stack.ss_size = SEGV_STACK_SIZE;
    sigaltstack(&segv_stack, NULL);

    if (!sigsetjmp(buf, 1)) {
        return BadF(n, p, k);
    }
    StackOverflowException(n, p, k);
    return 0;
}

// unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k) {
// 	if(p>0)return 1+BadF(n,p-1,k);
// 	//p==0
// 	if(n>0) return 1+BadF(n-1,k,k);
// 	return 0;
// }

// void StackOverflowException(unsigned long long n, unsigned long long p, unsigned long long k) {
//     printf("overflow %lld %lld %lld\n", n, p, k);
// }

// int main() {
//     // printf("%lld\n", BadFHandler(5000, 5000, 5000));
//     printf("%lld\n", BadFHandler(50, 50, 50));
//     printf("%lld\n", BadFHandler(10000, 10000, 10000));
//     printf("%lld\n", BadFHandler(1000, 1000, 1000));
//     return 0;
// }
