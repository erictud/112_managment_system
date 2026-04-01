#ifndef QUEUESTACK_H
#define QUEUESTACK_H

typedef struct Stack {
    void *data;
    struct Stack *next;
} Stack;

typedef struct QueueCell {
    void *data;
    struct QueueCell *next;
} QueueCell;

typedef struct Queue {
    int len;
    struct QueueCell *front, *rear;
} Queue;

// Queue methods
Queue *initQueue();
void enqueue(Queue *q, void *data);
void enqueueFirst(Queue *q, void *data);
void dequeue(Queue *q);
void freeQueue(Queue **q);
int isEmptyQueue(Queue *q);

// Stack methods
Stack *push(Stack *s, void *data);
Stack *pop(Stack *s);
Stack *top(Stack *s);
void freeStack(Stack *s);
int isEmptyStack(Stack *s);

#endif