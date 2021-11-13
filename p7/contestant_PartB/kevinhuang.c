#define HEAP_STACK_SIZE (1 << 30)

// declaration of the deeply recursive function.
unsigned long long BadF(unsigned long long n, unsigned long long p, unsigned long long k);

// If calling BadF(n,p,k) results in a stack overflow exception, call this
// function and use your code from part A to return the value of BadF(n,p,k).
void StackOverflowException(unsigned long long n, unsigned long long p, unsigned long long q);

// Your implementation of a Wrapper function.
unsigned long long BadFHandler(unsigned long long n, unsigned long long p, unsigned long long k)
{
    // some code here that calculates the result of BadF(n,p,k) using magic...

    char *heapStack = (char *)malloc(HEAP_STACK_SIZE) + HEAP_STACK_SIZE - 128;
    char s[(char *)&heapStack - heapStack];

    register void *esp asm("esp");
    int *flag = (int *)(esp - 2000000);
    *flag = 0x12345678;

    unsigned long long ans = BadF(n, p, k);

    if (*flag != 0x12345678)
    {
        StackOverflowException(n, p, k);
        return 0;
    }

    return ans;
}
