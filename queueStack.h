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

Queue *initQueue();
void enqueue(Queue *q, void *data);
int isEmptyQueue(Queue *q);
Stack *push(Stack *s, void *data);

#endif