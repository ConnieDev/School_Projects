#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "../command/command.h"
#include "../tokenize/makeArgs.h"


int containsPipe(Command * com, Command *** coms);
void pipeIt(Command ** coms, int pipeCount);
void doublePipeIt(char ** firstPipe, char ** secondPipe, char ** thirdPipe);
pid_t runInChild(Command * com, int stin, int stout);
int runSection(Command * com, int stin, int stout);
int countPipes(Command * com);
#endif 
