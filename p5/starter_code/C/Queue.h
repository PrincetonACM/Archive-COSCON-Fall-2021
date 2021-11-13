#ifndef QUEUE
#define QUEUE

typedef struct Queue* Queue_T;

Queue_T Queue_new();

void Queue_enqueue(Queue_T queue, void* item);

void* Queue_dequeue(Queue_T queue);

#endif
