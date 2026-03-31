#include <stdlib.h>
#include "linkedLists.h"


DoubleLinkedList *initList(void *dummyNodeData){
    Node *dummyNode = malloc(sizeof(DoubleLinkedList));
    dummyNode->prev = dummyNode->next = dummyNode;
    dummyNode->data = dummyNodeData;
    DoubleLinkedList *list = malloc(sizeof(DoubleLinkedList));
    list->head = list->tail = dummyNode;
    list->len = 0;
    return list;
}

