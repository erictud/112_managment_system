#include "queueStack.h"
#include <stdlib.h>

Queue *initQueue(){
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->len = 0;
    return q;
}

void enqueue(Queue *q, void *data){
    QueueCell *newNode = malloc(sizeof(QueueCell));
    newNode->data = data;
    newNode->next = NULL;
    if(q->front == NULL){
        q->front = q->rear = newNode;
    }else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->len++;
}

void dequeue(Queue *q) {
    if(q->front == NULL)
    return;
    if(q->front == q->rear) { // only element
        free(q->front);
        q->front = q->rear = NULL;
    } else {
        QueueCell *p = q->front;
        q->front = q->front->next;
        free(p);
    }
}

int isEmptyQueue(Queue *q){
    return q->front == NULL;
}

Stack *push(Stack *s, void *data) {
    Stack *t = malloc(sizeof(Stack));
    t->data = data;
    t->next = s;
    return t;
}