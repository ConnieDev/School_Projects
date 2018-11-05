#include "word.h"
#include "../utils/myUtils.h"


/**
 * @brief Prints the specific word.
 *
 * Format is word - length
 *
 * @param passedIn - The void * passed in representing a specific word
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void printTypeWord(void * passedIn)
{
	Word * w = (Word *)passedIn;
	printf("%s - %d\n", w->ltrs,w->len);

}// end printType


/**
 * @brief Builds and returns a single word.
 *
 * Reads the initial data from the file and then builds
 * an object of type word.
 *
 * @note The carriage return will be removed when reading from the file
 *
 * @param fin - The FILE * representing the open file
 * @return void * - Representing a word object
 *
 * @warning - The passed in FILE * fin is checked - exit(-99) if NULL
 */
void * buildTypeWord(FILE * fin)
{
	if(fin == NULL){
		perror("oops");
		exit(-99);
	}
	char ltr[100];
	int len;

	Word * temp = (Word*)calloc(1,sizeof(Word));
	fgets(ltr,100,fin);
	strip(ltr);
	temp->ltrs = (char*) calloc(strlen(ltr)+1,sizeof(char));
	strcpy(temp->ltrs,ltr);
	len = strlen(ltr);
	temp->len = len;
    return temp;
}// end buildType


/**
 * @brief Builds and returns a single word.
 *
 * Reads the initial data from the keyboard by prompting the user.
 * A word object is constructed.
 *
 * @note The carriage return will be removed when reading from the keyboard
 *
 * @return void * - Representing a word object
 *
 */
void * buildTypeWord_Prompt()
{
	printf("enter a word...");
    return buildTypeWord(stdin);
}// end buildType_Prompt


/**
 * @brief Compares two objects of type word.
 *
 * Words are compared based on the letters (word)
 *
 * @note The passed in items will need to be cast to the appropriate word type.
 *
 * @param p1 - The void * representing an object of type word
 * @param p2 - The void * representing an object of type word
 * @return int - Representing order < 0 indicates p1 is less than p2,
 * > 0 indicates p1 is greater than p2 and == 0 indicates p1 == p2 for contents
 *
 * @warning - The passed in void * p1 is checked - exit(-99) if NULL
 * @warning - The passed in void * p2 is checked - exit(-99) if NULL
 */
int compareWords(const void * p1, const void * p2)
{
	Word * S1 = (Word*)p1;
	Word * S2 = (Word*)p2;
		return strcmp(S1->ltrs, S2->ltrs);
   return 0;
}// end compare


/**
 * @brief Cleans up all dynamically allocated memory for the word
 *
 * Cleans up and frees all the dynamically allocated memory 
 * In this case ltrs
 *
 * Each pointer in the specific data type is set to NULL after it has been freed.
 *
 * @param passedIn - The void * passed in representing the specific word
 *
 * @warning - The passed in void * passedIn is checked - exit(-99) if NULL
 */
void cleanTypeWord(void * ptr)
{
	Word * w = (Word *)ptr;
		free(w->ltrs);
		w->ltrs = NULL;
		free(w);
		w = NULL;
}// end cleanType
