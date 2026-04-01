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

void delFromList(DoubleLinkedList *list, int id, int (*cmp)(void *data, int id)){
    Node *p = list->head->next;
    while(p != list->head){
        if(cmp(p->data, id) == 1){
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
            return;
        }
        p = p->next;
    }
}

void freeList(DoubleLinkedList **list, int cleanData){
    Node *p = (*list)->head->next, *q;
    while(p != (*list)->head){
        q = p;
        p = p->next;
        free(q);
    }
    free((*list)->head->data);
    free((*list)->head);
    free(*list);
}