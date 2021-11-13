#include <stdlib.h>
#include "Stack.h"

static int ops = 0;

struct Node {
    void* item;
    struct Node* below;
};

struct Stack {
    struct Node* top;
    int size;
};

Stack_T Stack_new() {
    Stack_T stack = (Stack_T) malloc(sizeof(struct Stack));
    stack->top = NULL;
    stack->size = 0;
}

void Stack_free(Stack_T stack) {
    struct Node* next;
    struct Node* current = stack->top;
    while (current != NULL) {
        next = current->below;
        free(current);
        current = next;
    }

    free(stack);
}

// Pushes item onto the stack.
void Stack_push(Stack_T stack, void* item) {
    ops++;
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    new->below = stack->top;
    new->item = item;
    stack->top = new;
    stack->size++;
}

// Pops and returns the item from the top of the stack.
void* Stack_pop(Stack_T stack) {
    ops++;
    struct Node* remove = stack->top;
    void* item = remove->item;
    stack->top = remove->below;
    stack->size--;
    free(remove);
    return item;
}

// Returns the number of items on the stack. Does not count as an operation.
int Stack_size(Stack_T stack) {
    return stack->size;
}

int getOperationCount() {
    return ops;
}
