#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../command/command.h"
#include "../aliases/alias.h"
struct node
{
    void * data;
    int ind;
    struct node * next;
    struct node * prev;
};
typedef struct node Node;

struct linkedlist
{
    Node * head;
    int size;
};
typedef struct linkedlist LinkedList;

LinkedList * linkedList();


void addLast(LinkedList * theList, Node * nn, int localSize, void (*removeData)(void *));
void addFirst(LinkedList * theList, Node * nn);
void removeFirst(LinkedList * theList, void (*removeData)(void *));
void removeLast(LinkedList * theList, void (*removeData)(void *));
void removeItem(LinkedList * theList, void * (*buildType)(FILE * stream), void (*removeData)(void *), int (*compare)(const void *, const void *));
void clearList(LinkedList * theList, void (*removeData)(void *));
void printList(const LinkedList * theList, void (*convertData)(int ,void *));
void apendListToFile(FILE * fp, const LinkedList * theList, char *(*toString)(void *), int fileSize);
void * getLast(LinkedList * theList);
void * getIndex(LinkedList * theList, char * s);
#endif // LINKEDLIST_H
