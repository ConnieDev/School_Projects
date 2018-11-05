#include "alias.h"

#include "../utils/myUtils.h"

void printTypeAlias(void * passedIn)
{
	Alias * a = (Alias *)passedIn;
	printf("%s=\"%s\"\n",a->als, toStringTypeCommand(a->com));

}// end printType

void printTypeAliasFile(void * passedIn, FILE * fp)
{
	Alias * a = (Alias *)passedIn;
	fprintf(fp, "%s=\"%s\"\n",a->als, toStringTypeCommand(a->com));
}

void * buildTypeAlias(char * s, int count)
{
	if(s == NULL){
		perror("oops");
		exit(-99);
	}
	char copy[100];
	strcpy(copy,s);
	char * save = NULL;
	char * token = strtok_r(copy, "=", &save);
	Alias * temp = (Alias*)calloc(1,sizeof(Alias));
	strip(token);
	temp->als = (char*) calloc(strlen(token)+1,sizeof(char));
	strcpy(temp->als,token);
	token = strtok_r(NULL, "", &save);
	strip(token);
	token++;
	token[strlen(token)-1] = 0;
	temp->com = buildTypeCommand(token);
    return temp;
}// end buildType

void cleanTypeAlias(void * ptr)
{
	Alias * a = (Alias *)ptr;
	free(a->als);
	a->als = NULL;
	cleanTypeCommand(a->com);
	free(a);
	a = NULL;
}// end cleanType
