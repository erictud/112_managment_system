#include "queueStack.h"
#include <stdlib.h>

Queue *initQueue(){
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->len = 0;
    return q;
}