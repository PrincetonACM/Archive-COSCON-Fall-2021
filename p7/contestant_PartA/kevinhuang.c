#define HEAP_STACK_SIZE (1 << 30)

// declaration of the deeply recursive function.
unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k);

// Your implementation of a Wrapper function.
unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k) {
    // some code here that calculates the result of BadF(n,p,k) using magic...

    char* heapStack = (char*)malloc(HEAP_STACK_SIZE) + HEAP_STACK_SIZE - 128;
    char s[(char*)&heapStack - heapStack];
    return BadF(n,p,k);
}
