#include "tokenize.h"

void clean(int argc, char **argv)
{
	int i;
	for(i = 0; i < argc; i++){
		free(argv[i]);

	}
	free(argv);


}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
	char save[100];
	char * cache = NULL;
	int count = 0;
	int i;

	strcpy(save, s);

	char * token = strtok_r(save, " ", &cache);
	while(token != NULL){
		count++;
		token = strtok_r(NULL, " ", &cache);
	}
	if(count == 0){
		return -1;
	}

	(*argv) = (char**)calloc(count +1, sizeof(char*));
	token = strtok_r(s, " ", &cache);
	for(i = 0; i < count; i++){
		(*argv)[i] = (char*)calloc(strlen(token)+1, sizeof(char));
		strcpy((*argv)[i], token);
		token = strtok_r(NULL, " ", &cache);
	}

   return count;

}// end makeArgs
