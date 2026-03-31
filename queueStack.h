#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueCell {
    void *data;
    struct QueueCell *next;
} QueueCell;

typedef struct Queue {
    int len;
    struct QueueCell *front, *rear;
} Queue;

Queue *initQueue();

#endif