#include "myUtils.h"

void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(array), x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;

}// end while
   
}// end strip

int menu()
{
   char temp[MAX];
   int choice;
   printf("1) Print the list - MyInt\n");
   printf("2) Add First - MyInt\n");
   printf("3) Add Last - MyInt\n");
   printf("4) Sort - MyInt\n");
   printf("5) Remove First - MyInt\n"); 
   printf("6) Remove Last - MyInt\n");
   printf("7) Remove Item - Word\n");
   printf("8) Quit\n");
   printf("Choice --> ");
   fgets(temp, MAX, stdin);
   choice = atoi(temp);

   
   while(choice < 1 || choice > 8)
   {
   	printf("1) Print the list - Word\n");
   	printf("2) Add First - Word\n");
   	printf("3) Add Last - Word\n");
   	printf("4) Sort - Word\n");
	printf("5) Remove First - Word\n");
	printf("6) Remove Last - MyInt\n");
   	printf("7) Remove Item - Word\n");
   	printf("8) Quit\n");
   	printf("Choice --> ");
   	fgets(temp, MAX, stdin);
   	choice = atoi(temp);
   
   }// end while

   return choice;
   
}// end menu

