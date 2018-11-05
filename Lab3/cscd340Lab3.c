/**
 * The file that contains main is meant to
 * test your generic linked class using a basic
 * set of functions.
 *
 * @note This file will never be changed
 */
#include "./utils/myUtils.h"
#include "./utils/fileUtils.h"
#include "./linkedlist/listUtils.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/requiredIncludes.h"

int main(){

	int total = 5, choice;
	FILE * fin = NULL;

	LinkedList * intList = linkedList();
	buildListTotal(intList, total, stdin, buildInt);

	do
	{
		choice = menu();

		switch(choice){

		// MyInt
		case 1: printList(intList, printInt);
		break;

		case 2: addFirst(intList, buildNode(stdin, buildInt));
		break;

		case 3: addLast(intList, buildNode(stdin, buildInt));
		break;

		case 4: sort(intList, compareInt);
		break;

		case 5: removeFirst(intList, cleanInt);
		break;

		case 6: removeLast(intList, cleanInt);
		break;

		case 7: removeItem(intList, buildInt, cleanInt, compareInt);
		break;

		}// end switch

	}while(choice != 8);

	clearList(intList, cleanInt);
	free(intList->head);
	free(intList);
	intList = NULL;

	printf("Program Ended\n");

	return 0;

}// end main
