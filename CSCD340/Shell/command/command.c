#include "command.h"


void printTypeCommand(int index, void * passedIn){
	Command * c = (Command *)passedIn;
	printf(" %d %s\n", index, c->str);
}

void printArgs(Command * com, int a){
	for(int t = a; com->argv[t] != NULL ; t++){
		printf("%s\n", com->argv[t]);
	}
}

char * toStringTypeCommand(void * passedIn){
	Command * c = (Command *)passedIn;
	return c->str;
}

Command * buildTypeCommand(char * s)
{
	char *pos;
	if ((pos=strchr(s, '\n')) != NULL)
	    *pos = '\0';
	char copy[100];
	strcpy(copy,s);

	Command * temp = (Command*)calloc(1,sizeof(Command));
	temp->str = (char*) calloc(strlen(copy)+1,sizeof(char));
	strcpy(temp->str,copy);
	temp->argc = makeargs(s, &temp->argv);

    return temp;
}// end buildType

void cleanTypeCommand(void * ptr)
{
	Command * c = (Command *)ptr;
		free(c->str);
		c->str = NULL;
		clean(c->argc, c->argv);
		free(c);
		c = NULL;
}// end cleanType

