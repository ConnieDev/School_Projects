#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "../linkedlist/linkedList.h"
#include "../linkedlist/listUtils.h"
#include "../command/command.h"

void addPath(char * s);
int readHistory(FILE * fp, LinkedList * history, int fileSize, int localSize);
void changeDirectory(char * s);
int getFileLength(FILE * fp);
void truncateFile(FILE * fp, int allowedLength);
void printCWD();
void runCommand(Command * com);
void readRC(FILE * fp, LinkedList * alias, int * HISTFILECOUNT, int * HISTCOUNT);
void overwritePath(char * s);
#endif
