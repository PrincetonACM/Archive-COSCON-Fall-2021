// declaration of the deeply recursive function.
unsigned long long BadF(unsigned long long n,
unsigned long long p, unsigned long long k);

// Your implementation of a Wrapper function.
unsigned long long BadFHandler(unsigned long long n, unsigned long long p,
unsigned long long k) {
    static char stack[1 << 30];
    unsigned long long a = (unsigned long long)stack + (1 << 29);
    asm(
        "push  %rbp \n\t"
        "mov   %rsp, %rbp \n\t"
        "mov   %rax, %rsp \n\t"
        "call  BadF \n\t"
        "mov   %rbp, %rsp \n\t"
        "pop   %rbp \n\t"
    );
}
