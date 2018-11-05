#include "genericArray.h"

GenericArray * fillArray(FILE * in, int length, void * (*buildType)(FILE * input))
{
	GenericArray * array = (GenericArray *) calloc(length, sizeof(GenericArray));
	int x;
	for(x = 0; x < length; x++){
		array[x].data = buildType(in);
	}
	return array;
	
}


void printArray(GenericArray * array, int length, void (*printType)(void *))
{
	int x;
	printf("\n");
	for(x = 0; x < length; x++)
		printType(array[x].data);
	
	printf("\n");
}


void cleanArray(GenericArray * array, int length, void (*cleanType)(void *))
{
	int x;
	for(x = 0; x < length; x++)
		cleanType(array[x].data);
	
	free(array);
	array = NULL;

}

void sortArray(GenericArray * array, int length, int (*compar)(const void * v1, const void * v2))
{
	void * tempp;
	int temp;
	for(int i = 0; i < length; i++){
		temp = i;
		for(int x = i; x < length; x++){
			if(compar (array[temp].data, array[x].data) > 0){
				temp = x;
			}
		}
		tempp = array[i].data;
		array[i].data = array[temp].data;
		array[temp].data = tempp;
	}
}


