#include "./pipes/pipes.h"
#include "./command/command.h"
#include "./aliases/alias.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./linkedlist/listUtils.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/requiredIncludes.h"

int main()
{

	int argc, pipeCount;
	char **argv = NULL, s[MAX];
	int firstCount = 0, secondCount = 0, thirdCount = 0;
	char ** firstPipe = NULL, ** secondPipe = NULL, ** thirdPipe = NULL;
	int HISTCOUNT = 1000, HISTFILECOUNT = 2000;
	Command * c = NULL;
	Command ** coms;
	LinkedList * history = linkedList();
	LinkedList * aliases = linkedList();
	FILE * ussh_history;
	FILE * usshrc;

	readRC(usshrc, aliases, &HISTFILECOUNT, &HISTCOUNT);

	int histFileLength = getFileLength(ussh_history);
	int count = 0;

	count = readHistory(ussh_history, history, histFileLength, HISTCOUNT);
	ussh_history = fopen(".ussh_history", "a");
	printCWD();
	printf("command?: ");
	fgets(s, MAX, stdin);
	strip(s);
	coms = (Command**)calloc(count+1, sizeof(Command *));
	coms[0] = buildTypeCommand(s);
	while(strcmp(coms[0]->argv[0], "exit") != 0)
	{
		pipeCount = countPipes(coms[0]);
		if(pipeCount == 0){
			if(strcmp(coms[0]->argv[0], "!!") == 0){
				coms[0] = (Command*)getLast(history);
			}else if(strncmp(coms[0]->argv[0], "!", 1) == 0){
				coms[0] = (Command*)getIndex(history, coms[0]->argv[0]);
			}
			for(	Node *cur = aliases->head->next; cur != NULL; cur = cur->next){
				if(strcmp(coms[0]->argv[0], ((Alias*)cur->data)->als) == 0){
					coms[0] = ((Alias*)cur->data)->com;
				}
			}
		}
		pipeCount = containsPipe(coms[0], &coms);
		if (pipeCount > 0){
			for(int i = 0; i <= pipeCount; i++){
				if(strcmp(coms[i]->argv[0], "!!") == 0){
					coms[i] = (Command*)getLast(history);
				}else if(strncmp(coms[i]->argv[0], "!", 1) == 0){
					coms[i] = (Command*)getIndex(history, coms[i]->argv[0]);
				}
				for(Node *cur = aliases->head->next; cur != NULL; cur = cur->next){
					if(strcmp(coms[i]->argv[0], ((Alias*)cur->data)->als) == 0){
						coms[i] = ((Alias*)cur->data)->com;
					}
				}
			}
		}

		if(pipeCount > 0)
		{
			count++;
			pipeIt(coms, pipeCount);
			addLast(history, buildNode_TypePipe(coms, count, pipeCount), HISTCOUNT, cleanTypeCommand);

		}else{
			if(strcmp(coms[0]->argv[0], "history") == 0){
				count++;
				addLast(history, buildNode_Type(coms[0], count), HISTCOUNT, cleanTypeCommand);
				printList(history, printTypeCommand);
			}else if(strncmp(s, "PATH=$PATH:", 11) == 0){
				count++;
				addPath(s);
				addLast(history, buildNode_Type(coms[0], count), HISTCOUNT, cleanTypeCommand);
			}else if(strncmp(s, "PATH=", 5) == 0){
				count++;
				overwritePath(s);
				addLast(history, buildNode_Type(coms[0], count), HISTCOUNT, cleanTypeCommand);
			}else if(strcmp(coms[0]->argv[0], "cd") == 0){
				count++;
				changeDirectory(coms[0]->argv[1]);
				addLast(history, buildNode_Type(coms[0], count), HISTCOUNT, cleanTypeCommand);
			}else if(strcmp(coms[0]->argv[0], "exit") == 0){
				count++;
				addLast(history, buildNode_Type(coms[0], count), HISTCOUNT, cleanTypeCommand);
				break;
			}else{
				count++;
				runCommand(coms[0]);
				addLast(history, buildNode_Type(coms[0], count), HISTCOUNT, cleanTypeCommand);
			}
		}
		printCWD();
		printf("command?: ");
		fgets(s, MAX, stdin);
		strip(s);
		coms[0] = buildTypeCommand(s);

	}// end while

	apendListToFile(ussh_history, history, toStringTypeCommand, histFileLength);
	truncateFile(ussh_history, HISTFILECOUNT);
	clearList(history, cleanTypeCommand);
	free(history->head);
	free(history);
	history = NULL;
	clearList(aliases, cleanTypeAlias);
	free(aliases->head);
	free(aliases);
	aliases = NULL;
	return 0;

}// end main

