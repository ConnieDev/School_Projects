#include "listUtils.h"

Node * buildNode( FILE * in, void *(*buildData)(FILE * fin) )
{
	Node * nn = (Node *)calloc(1,sizeof(Node));
	nn->data = buildData(in);
    return nn;

}// end buildNode

Node * buildNode_Type(void * passedIn, int count)
{
	Node * nn = (Node *)calloc(1,sizeof(Node));
	nn->data = passedIn;
	return nn;
   
}// end buildNode_Type

Node * buildNode_TypePipe(Command ** passedIn, int count, int pipeCount)
{
	char copy[100] = "";
	for(int i = 0; i <= pipeCount; i++){
		strcat(copy, passedIn[i]->str);
		if(i < pipeCount){
			strcat(copy, "|");
		}
	}
	Node * nn = (Node *)calloc(1,sizeof(Node));
	nn->data = buildTypeCommand(copy);
	return nn;

}// end buildNode_Type


void buildListTotal(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in) )
{
    int x;
    Node * nn = NULL;
    
    for(x = 0; x < total; x++){
    	nn = (Node *)calloc(1,sizeof(Node));
    	nn->data = buildData(fin);
    	addFirst(myList, nn);
    }

}// end buildListTotal


void sort(LinkedList * theList, int (*compare)(const void *, const void *))
{
    Node * start, *search, *min;
    void * temp;

    if(theList->size > 1)
    {

        for(start = theList->head->next; start->next != NULL; start = start->next)
        {
            min = start;

            for(search = start->next; search != NULL; search = search->next)
                if(compare(search->data, min->data) < 0)
                    min = search;

            temp = start->data;
            start->data = min->data;
            min->data = temp;

        }// end for start

    }// end if
}// end sort
