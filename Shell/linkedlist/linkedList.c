#include "linkedList.h"

LinkedList * linkedList()
{
	LinkedList * List = (LinkedList*)calloc(1, sizeof(LinkedList));
	Node * nn = (Node*)calloc(1,sizeof(Node));
	nn->data = NULL;
	nn->next = NULL;
	nn->prev = NULL;
	nn->ind = 0;
	List->head = nn;
	return List;
}// end linkedList


void clearList(LinkedList * theList, void (*removeData)(void *))
{
    if(theList->size != 0){
    	Node * cur = theList->head->next;
    	Node * temp;
    	while(cur != NULL){
    		temp = cur;
    		cur = cur->next;
    		removeData(temp->data);
    		temp->data = NULL;
    		free(temp);
    	}
    }
}// end clearList

void apendListToFile(FILE * fp, const LinkedList * theList, char* (*toString)(void *), int fileSize)
{
	if(theList->size != 0){
		char a[100];
		Node * cur = theList->head->next;
		while(cur != NULL){
			if(cur->ind > fileSize){
				fprintf(fp,"%s\n", toString(cur->data));
			}
			cur = cur->next;
		}
	}
	fclose(fp);
}

void printList(const LinkedList * theList, void (*convertData)(int ,void *))
{
	if(theList->size != 0){
		Node * cur = theList->head->next;
		while(cur != NULL){
			convertData(cur->ind, cur->data);
			cur = cur->next;
		}
	}
}// end printList

void addLast(LinkedList * theList, Node * nn, int localSize, void (*removeData)(void *))
{
	if(theList->head->next == NULL){
		addFirst(theList, nn);
	}else{
		Node * cur = theList->head->next;
		while(cur->next != NULL){
			cur = cur->next;
		}
		cur->next = nn;
		nn->prev = cur;
		theList->size++;
		nn->ind = theList->size;
		if(localSize != -1){
			if(theList->size > localSize){
				removeFirst(theList, removeData);
			}
		}
	}
}// end addLast

void addFirst(LinkedList * theList, Node * nn)
{
	nn->next = theList->head->next;
	nn->prev = theList->head;
	if(nn->next != NULL){
		nn->next->prev = nn;
	}
	theList->head->next = nn;
	nn->ind = 1;
	theList->size++;
	for(Node *cur = nn->next; cur != NULL; cur = cur->next){
		cur->ind++;
	}
}// end addFirst

void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
	Node * temp = theList->head->next;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->next=NULL;
	temp->prev = NULL;
	removeData(temp->data);
	free(temp);
	temp = NULL;
	for(Node *cur = theList->head->next; cur != NULL; cur = cur->next){
		cur->ind--;
	}
}// end removeFirst

void removeLast(LinkedList * theList, void (*removeData)(void *))
{
	Node * cur = theList->head->next;
	Node * temp;
	while(cur->next != NULL){
		temp = cur;
		cur = cur->next;
	}
	temp->next = NULL;

	cur->prev = NULL;
	removeData(cur->data);
	free(cur);
	cur = NULL;

}// end removeLast

void * getLast(LinkedList * theList)
{
	Node * cur = theList->head;
	void * temp;
	while(cur->next != NULL){
		cur = cur->next;
		temp = cur->data;
	}
	return temp;
}

void * getIndex(LinkedList * theList, char * s){
	Node * cur = theList->head->next;
	void * temp = NULL;
	char * copy;
	char l[100];
	copy = strdup(s+1);
	strcpy(l, copy);
	int t = atoi(l);
	while(cur != NULL){
		if((cur->ind - t) == 0){
			temp = cur->data;
			cur = NULL;
		}else{
			cur = cur->next;
		}
	}
	if(temp == NULL){
		return NULL;
	}
	return temp;
}

void removeItem(LinkedList * theList, void * (*buildType)(FILE * stream), void (*removeData)(void *), int (*compare)(const void *, const void *))
{
	Node * cur = theList->head->next;
	Node * temp = theList->head;
	Node * remo = (Node*)calloc(1, sizeof(Node));
	remo->data = buildType(stdin);

	while(compare(cur->data, remo->data) != 0 && cur != NULL){
		temp = cur;
		cur = cur->next;
	}
	if(cur != NULL){
		cur->prev = NULL;
		temp->next = cur->next;
		if(cur->next != NULL){
			cur->next->prev = temp;
		}
		cur->next = NULL;
		removeData(remo->data);
		free(remo);
		remo = NULL;
		removeData(cur->data);
		while(cur != NULL){
			cur->ind--;
			cur = cur->next;
		}
		free(cur);
		cur = NULL;

	}

}// end removeItem


