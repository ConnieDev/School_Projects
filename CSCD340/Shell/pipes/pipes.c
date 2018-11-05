#include "pipes.h"
#include "../command/command.h"

int containsPipe(Command * com, Command *** coms)
{
	int i, count = 0;
	for(i = 0; i < com->argc ; i++){
		if(strcmp(com->argv[i], "|")==0){
			count++;
		}
	}
	if(count > 0){
		char copy[100];
		char * save, * token;
		strcpy(copy, com->str);

		token = strtok_r(copy, "|", &save);
		(*coms)[0] = buildTypeCommand(token);
		for(int x = 1; x < count+1; x++)
		{
			token = strtok_r(NULL, "|", &save);
			(*coms)[x] = buildTypeCommand(token);
		}
	}
	return count;
}// end containsPipe

int countPipes(Command * com){
	int i, count = 0;
	for(i = 0; i < com->argc ; i++){
		if(strcmp(com->argv[i], "|")==0){
			count++;
		}
	}
	return count;
}

void pipeIt(Command ** coms, int pipeCount)
{
	int n, a = 0, i;
	int p1[2], p2[2];
	pipe(p1);
	runSection(coms[0], 0, p1[1]);
	close(p1[1]);
	for(i = 1; i < pipeCount; i++){
		if(i % 2){
			pipe(p2);
			runSection(coms[i], p1[0], p2[1]);
			close(p1[0]);
			close(p2[1]);
		}else{
			pipe(p1);
			runSection(coms[i], p2[0], p1[1]);
			close(p2[0]);
			close(p1[1]);
		}
	}
	if(i % 2){
		runSection(coms[i], p1[0], 1);
		close(p1[0]);
	}else{
		runSection(coms[i], p2[0], 1);
		close(p2[0]);
	}

}// end pipeIt

int runSection(Command * com, int stin, int stout){
	pid_t child_pid;
	child_pid = runInChild(com, stin, stout);
	int status;
	waitpid(child_pid, &status, 0);
	return 0;
}

pid_t runInChild(Command * com, int stin, int stout){
	pid_t child;
	if((child = fork())){
		return child;
	}
	if(stout == 1){
		dup2(stin, 0);
	}else if(stin == 1){
		dup2(stout, 1);
	}else{
		dup2(stin,0);
		dup2(stout,1);
	}

	execvp(com->argv[0], com->argv);
	exit(-1);
}


