#ifndef STACK
#define STACK

typedef struct Stack* Stack_T;

// Returns pointer to new stack.
Stack_T Stack_new();

// Frees memory used by stack.
void Stack_free(Stack_T stack);

// Pushes item onto the stack.
void Stack_push(Stack_T stack, void* item);

// Pops and returns the item from the top of the stack.
void* Stack_pop(Stack_T stack);

// Returns the number of items on the stack. Does not count as an operation.
int Stack_size(Stack_T stack);

// For testing purposes.
int getOperationCount();

#endif
