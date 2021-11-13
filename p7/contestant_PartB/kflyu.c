// declaration of the deeply recursive function.
unsigned long long BadF(unsigned long long n,
unsigned long long p, unsigned long long k);

void StackOverflowException(unsigned long long n,
unsigned long long p, unsigned long long k);

static sigjmp_buf hhhhhhhh_buf;

void hhhhhhhh(int signo) {
    siglongjmp(hhhhhhhh_buf, 1);
}


unsigned long long BadFHandler(unsigned long long n, unsigned long long p,
unsigned long long k) {
    unsigned long long res;
    stack_t sa, sa_old;
    struct sigaction act = { 0 }, old_act;

    sa.ss_sp = malloc(SIGSTKSZ);
 	sa.ss_size = SIGSTKSZ;
 	sa.ss_flags = SS_ONSTACK;

    sigaltstack(&sa, &sa_old);

    act.sa_flags = SA_ONSTACK;
    act.sa_handler = &hhhhhhhh;

    sigaction(SIGSEGV, &act, &old_act);
    if (sigsetjmp(hhhhhhhh_buf, 1)) {
        StackOverflowException(n, p, k);
        res = 0;
    } else {
        res = BadF(n, p, k);
    }

    sigaltstack(&sa_old, NULL);
    sigaction(SIGSEGV, &old_act, NULL);
    free(sa.ss_sp);
    return res;
}
