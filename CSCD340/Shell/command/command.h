#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/myUtils.h"
#include "../tokenize/makeArgs.h"


struct command {char ** argv; int argc; char * str;};

typedef struct command Command;

void printTypeCommand(int index, void * passedIn);
void cleanTypeCommand(void * ptr);
Command * buildTypeCommand(char * s);
char * toStringTypeCommand(void * passedIn);
void printArgs(Command * com, int a);
#endif
