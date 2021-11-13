// #include <stdlib.h>
// #include <memory.h>
// #include <signal.h>
// #include <unistd.h>
// #include <setjmp.h>
// #include <string.h>
// #include <stdio.h>

unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k);
// {
// 	if(p>0)return 1+BadF(n,p-1,k);
// 	//p==0
// 	if(n>0) return 1+BadF(n-1,k,k);
// 	return 0;
// }

unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k) {
    long sp = 0;

    long size = (long)1 << 30;  // chars
    char *mystack = (char *)malloc(size);
    char *top = mystack + size - 1;

    // Save SP and set SP to our newly created
    // stack frame
    asm ("mov %%rsp,%0; \n\t  mov %1,%%rsp": "=a"(sp) :"b"(top) :);

    // call bad code here
    unsigned long long result = BadF(n, p, k);
    /// int result = 0;

    // restore old SP so we can return to OS
    asm ("mov %0,%%rsp": : "a"(sp) :);

    free(mystack);
    return result;
}

// int main() {
//     printf("%lld\n", BadFHandler(5000, 5000, 5000));
//     // printf("%lld\n", BadFHandler(1000, 1000, 1000));
//     return 0;
// }
