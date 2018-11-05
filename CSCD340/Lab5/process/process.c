#include "process.h"
#include <sys/wait.h>
#include <unistd.h>

void forkIt(char ** argv)
{
	pid_t childpid;
	int n;
	childpid = fork();

	if (childpid != 0){
		waitpid(childpid, &n, 0);
	}else{
		execvp(argv[0], argv);
		exit(-1);
	}
}
