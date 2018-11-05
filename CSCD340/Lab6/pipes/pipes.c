#include "pipes.h"
#include "../tokenize/makeArgs.h"
int containsPipe(char *s)
{
	int i, count = 0;
	for(i = 0; i < strlen(s); i++){
		if(s[i] == '|'){
			count++;
		}
	}
	printf("number of Pipes: %d\n", count);
	return count;
}// end containsPipe


char ** parsePrePipe(char *s, int * preCount)
{
	char copy[MAX];
	strcpy(copy, s);
	char ** argv = NULL, * token = NULL, * save = NULL;

	token = strtok_r(copy, "|", &save);
	*preCount = makeargs(token,&argv);
	printf("PrePipe String: ");
	for(int i = 0; i < *preCount; i++){
		printf("%s", argv[i]);
	}
	printf("\n");
	return argv;
}// end parsePrePipe


char ** parsePostPipe(char *s, int * postCount)
{
	char copy[MAX];
	strcpy(copy, s);
	char **argv = NULL, *token = NULL, *save = NULL;

	token = strtok_r(copy, "|", &save);
	*postCount = makeargs(save, &argv);
	printf("PrePipe String: ");
	for(int i = 0; i < *postCount; i++){
		printf("%s", argv[i]);
	}
	printf("\n");
	return argv;
}// end parsePostPipe

void pipeIt(char ** prePipe, char ** postPipe)
{
	int n;
	pid_t pid = fork();

	if(pid != 0){
		waitpid(pid, &n, 0);
	}else{
		int fd[2];
		pipe(fd);
		pid_t pid1 = fork();
		if(pid1 != 0){
			//wc-w stuff
			close(fd[1]);
			close(0);
			dup(fd[0]);
			close(fd[0]);
			execvp(postPipe[0], postPipe);
			exit(-1);
		}else{
			//ls-l stuff
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			execvp(prePipe[0], prePipe);
			exit(-1);
		}
	}
}// end pipeIt

