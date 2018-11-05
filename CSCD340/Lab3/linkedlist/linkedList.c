#include "linkedList.h"

LinkedList * linkedList()
{
	LinkedList * List = (LinkedList*)calloc(1, sizeof(LinkedList));
	Node * nn = (Node*)calloc(1,sizeof(Node));
	nn->data = NULL;
	nn->next = NULL;
	nn->prev = NULL;
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

void printList(const LinkedList * theList, void (*convertData)(void *))
{
   if(theList->size == 0){
	   printf("Empty List...");
   }else{
	   Node * cur = theList->head->next;
	   while(cur != NULL){
		   convertData(cur->data);
		   cur = cur->next;
	   }
	   printf("\n");
   }

}// end printList

void addLast(LinkedList * theList, Node * nn)
{
	if(theList->head->next == NULL){
		addFirst(theList, nn);
	}
	Node * cur = theList->head->next;
	while(cur->next != NULL){
		cur = cur->next;
	}
	cur->next = nn;
	nn->prev = cur;
	theList->size++;
}// end addLast

void addFirst(LinkedList * theList, Node * nn)
{
	nn->next = theList->head->next;
	nn->prev = theList->head;
	if(nn->next != NULL){
		nn->next->prev = nn;
	}
	theList->head->next = nn;
	theList->size++;
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
		free(cur);
		cur = NULL;
	}

}// end removeItem

