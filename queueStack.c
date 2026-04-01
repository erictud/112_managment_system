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

// add element to the start of the queue
void enqueueFirst(Queue *q, void *data){
    QueueCell *newNode = malloc(sizeof(QueueCell));
    newNode->data = data;
    newNode->next = q->front;
    if(q->front == NULL){
        q->front = q->rear = newNode;
    }else{
        q->front = newNode;
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
    q->len--;
}

int isEmptyQueue(Queue *q){
    return q->front == NULL;
}

void freeQueue(Queue **q){
    QueueCell *p = (*q)->front, *aux;
    while(p != NULL){
        aux = p;
        p = p->next;
        free(aux);
    }
    free(*q);
}

Stack *push(Stack *s, void *data) {
    Stack *t = malloc(sizeof(Stack));
    t->data = data;
    t->next = s;
    return t;
}

Stack *pop(Stack *s){
    s = s->next;
    return s;
}

Stack *top(Stack *s){
    if(s == NULL)
        return NULL;
    return s;
}

int isEmptyStack(Stack *s){
    return s == NULL;
}

void freeStack(Stack *s){
    Stack *p;
    while(s != NULL){
        p = s;
        s = s->next;
        free(p);
    }
}