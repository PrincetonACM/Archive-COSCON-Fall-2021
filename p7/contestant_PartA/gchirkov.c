#include <stdlib.h>
#include <memory.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>

// declaration of the deeply recursive function.
unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k);

// unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k) {
//     if (n <= 1) return 1;
//     return BadF(n-1, p, k) + 1;
// }

long long unsigned p1 = 0;
long long unsigned p2 = 0; 
long long unsigned p3 = 0;
long long unsigned res = 0;

void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    // printf("new segfault\n");
    // long long unsigned newk = ((ucontext_t*) arg)->uc_mcontext.gregs[12];
    // long long unsigned newp = ((ucontext_t*) arg)->uc_mcontext.gregs[9];
    // long long unsigned newn = ((ucontext_t*) arg)->uc_mcontext.gregs[8];
    // long long unsigned res = BadF(newn, newp, newk);
    res = BadF(p1, p2, p3);
}

void setup_signal_stuff()
{
    stack_t ss;
    long long unsigned ssize = 1024ULL*1024*1024*1024*1024;
    ss.ss_sp = NULL;
    while (ss.ss_sp == NULL) {
        ssize = ssize / 2;
        ss.ss_sp = malloc(ssize);
    }
    ss.ss_size = ssize;
    ss.ss_flags = 0;
    if (sigaltstack(&ss, NULL) == -1) {
       perror("sigaltstack");
       exit(EXIT_FAILURE);
    }


    struct sigaction act = {0};
    bzero(&act, sizeof(act));
    act.sa_sigaction = &segfault_sigaction;
    act.sa_flags = SA_SIGINFO | SA_NODEFER | SA_ONSTACK;

    if (sigaction(SIGSEGV, &act, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

// Your implementation of a Wrapper function.
unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k) {
    setup_signal_stuff();
    // int val = setjmp(env);
    // if (!val) return BadF(n,p,k); 
    // else return val;
    p1 = n;
    p2 = p;
    p3 = k;
    raise(SIGSEGV);
    return res;
}


// int main()
// {
//     printf("%lld\n", BadFHandler(175499000, 1, 1));
// }
