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


