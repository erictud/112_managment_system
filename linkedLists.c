#include <stdlib.h>
#include "linkedLists.h"

DoubleLinkedList *initList(void *dummyNodeData){
    Node *dummyNode = malloc(sizeof(Node));
    dummyNode->prev = dummyNode->next = dummyNode;
    dummyNode->data = dummyNodeData;
    DoubleLinkedList *list = malloc(sizeof(DoubleLinkedList));
    list->head = list->tail = dummyNode;
    list->len = 0;
    return list;
}

void addToList(DoubleLinkedList *list, void *data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->tail;
    newNode->prev = list->tail->prev;
    list->tail->prev->next = newNode;
    list->tail->prev = newNode;
}

// deleting a node from list based on a comparing node
void delFromList(DoubleLinkedList *list, int id, int (*cmp)(void *data, int id)){
    Node *p = list->head->next;
    while(p != list->head){
        if(cmp(p->data, id) == 1){
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
            return; // every node is unqiue
        }
        p = p->next;
    }
}

// freeing list nodes and making sure to free the dynamic content of every node
void freeList(DoubleLinkedList **list, void (*freeDynamicPart)(void *data)){
    Node *p = (*list)->head->next, *q;
    while(p != (*list)->head){
        q = p;
        p = p->next;
        if(freeDynamicPart)
            freeDynamicPart(q->data);
        free(q->data);
        free(q);
    }
    if(freeDynamicPart)
        freeDynamicPart((*list)->head->data);
    free((*list)->head->data);
    free((*list)->head);
    free(*list);
}