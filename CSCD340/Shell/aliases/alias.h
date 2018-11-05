#ifndef ALIAS_H_
#define ALIAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../command/command.h"

struct alias {char * als; Command * com;};

typedef struct alias Alias;

void cleanTypeAlias(void * ptr);
void * buildTypeAlias(char * s, int count);
void printTypeAlias(void * passedIn);
void printTypeAliasFile(void * passedIn, FILE * fp);

#endif
