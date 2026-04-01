#ifndef LINKED_H
#define LINKED_H

typedef struct Node {
    void *data;
    struct Node *next, *prev;
} Node;

typedef struct DoubleLinkedList {
    int len;
    struct Node *head, *tail;
} DoubleLinkedList;

DoubleLinkedList *initList(void *dummyNodeData);
void addToList(DoubleLinkedList *list, void *data);
void delFromList(DoubleLinkedList *list, int id, int (*cmp)(void *data, int id));
void freeList(DoubleLinkedList **list, int cleanData);
#endif