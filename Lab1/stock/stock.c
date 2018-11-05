#include "stock.h"
#include "../utils/myUtils.h"
/**
 * Build stock builds a Stock object by reading 3 lines from the file.  First line is the symbol,
 * second line is the company name, third line is the price.<br>
 * <br>
 * You must first build the Stock structure dynamically<br>
 * Then read in the symbol and allocate the memory for it, copy from temp into the new allocated memory<br>
 * Then read in the name and allocate the memory for it, copy from temp into the new allocated memory<br>
 * Then read in the price and assign it to the price struct data member
 *
 * @param fin Representing the FILE *
 * @return void * Representing a Stock object filled with data
 */ 
void * buildStock(FILE * fin)
{
	Stock* st = (Stock*)calloc(1,sizeof(Stock));
	char temp[100];


	fgets(temp, 100, fin);
	strip(temp);
	st->symbol = malloc(sizeof(temp));
	memcpy (st->symbol, temp, sizeof(temp));

	fgets(temp,100, fin);
	strip(temp);
	st->name = malloc(sizeof(temp));
	memcpy (st->name, temp, sizeof(temp));

	fgets(temp,100, fin);
	strip(temp);
	st->price = atof(temp);

	return st;
}


/**
 * The printStock method completes the following:<br>
 * 1) Receives a void pointer which it casts to a Stock *<br>
 * 2) Prints to the screen the the name - the symbol - the price
 */
void printStock(void * ptr)
{
	Stock * stock = (Stock *)ptr;
	printf("%s - %s - %f\n", stock->name, stock->symbol, stock->price);
}


/**
 * The cleanStock method completes the following:<br>
 * 1) Receives a void pointer which it casts to a Stock *<br>
 * 2) Frees the symbol<br>
 * 3) Frees the name<br>
 * 4) Sets the name and symbol to NULL
 * 5) Frees the Stock * for the structure
 *
 * @warning All pointers need to be set to NULL after they are freed
 */
void cleanStock(void * ptr)
{
	Stock * st = (Stock *)ptr;
	free(st->symbol);
	st->symbol = NULL;
	free(st->name);
	st->name = NULL;
	free(st);
	st = NULL;
}


/**
 * The compareSymbols compares the two stock symbols using strcmp<br>
 * 1) Cast s1 into a Stock *<br>
 * 2) Cast s2 into a Stock *<br>
 * 3) return strcmp of s1 symbol and s2 symbol
 * 
 * @param s1 Representing the array value to compare
 * @param s2 Representing the array value to compare
 * @return int Based on the strcmp results
 */
int compareSymbols(const void * s1, const void * s2)
{
	Stock * S1 = (Stock*)s1;
	Stock * S2 = (Stock*)s2;
	return strcmp(S1->symbol, S2->symbol);
}


/**
 * The compareNames compares the two stock names using strcmp<br>
 * 1) Cast s1 into a Stock *<br>
 * 2) Cast s2 into a Stock *<br>
 * 3) return strcmp of s1 name and s2 name
 * 
 * @param s1 Representing the array value to compare
 * @param s2 Representing the array value to compare
 * @return int Based on the strcmp results
 */
int compareNames(const void * s1, const void * s2)
{
	Stock * S1 = (Stock*)s1;
	Stock * S2 = (Stock*)s2;
	return strcmp(S1->name, S2->name);
}


/**
 * The comparePrices compares the two stock prices by multiplying each by 100 and then subtracting them<br>
 * 1) Cast s1 into a Stock *<br>
 * 2) Cast s2 into a Stock *<br>
 * 3) return s1 price * 100 - and s2 price * 100
 * 
 * @param s1 Representing the array value to compare
 * @param s2 Representing the array value to compare
 * @return int Based on the resultsof the subtraction
 */
int comparePrices(const void * s1, const void * s2)
{
	Stock * S1 = (Stock*)s1;
	Stock * S2 = (Stock*)s2;
	return (S1->price * 100) - (S2->price * 100);
}
