#ifndef LISTUTILS_H
#define LISTUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

#define MAX 100

Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) );
Node * buildNode_Type(void * passedIn, int count);
void sort(LinkedList * theList, int (*compare)(const void *, const void *));
void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in));
Node * buildNode_TypePipe(Command ** passedIn, int count, int pipeCount);

#endif // LISTUTILS_H
