#include "process.h"

void addPath(char * s){
	char newPath[100];
	char oldPath[1000];
	char * ret;
	ret = strchr(s, ':');
	ret++;
	strcpy(newPath, ret);
	strcpy(oldPath, getenv("PATH"));
	strcat(oldPath, ":");
	strcat(oldPath, newPath);
	setenv("PATH", oldPath, 1);
}
void overwritePath(char * s){
	char newPath[100];
	char * ret;
	ret = strchr(s, '=');
	ret++;
	strcpy(newPath, ret);
	setenv("PATH", newPath, 1);
}

int readHistory(FILE * fp, LinkedList * history, int fileSize, int localSize){
	fp = fopen(".ussh_history", "r");
	int count = 0;
	if(fp != NULL){

		char s[100];
		if(fileSize > localSize){
			int skip = (fileSize - localSize);
			while(fgets(s,sizeof s,fp)!= NULL){
				count++;
				if(count > skip){
					Command * c = buildTypeCommand(s);
					addLast(history, buildNode_Type(c, count), localSize, cleanTypeCommand);
				}
			}
		}else{
			while(fgets(s,sizeof s,fp)!= NULL){
				count++;
				Command * c = buildTypeCommand(s);
				addLast(history, buildNode_Type(c, count), localSize, cleanTypeCommand);
			}
		}
		fclose(fp);
	}
	return count;
}

void changeDirectory(char * s){
	char dir[100];
	strcpy(dir, s);
	chdir(dir);
}

int getFileLength(FILE * fp){
	fp = fopen(".ussh_history", "r");
	int count = 0;
	if(fp != NULL){
		for (int c = getc(fp); c != EOF; c = getc(fp)){
			if (c == '\n'){
				count = count + 1;
			}
		}
		fclose(fp);
	}
	return count;
}

void truncateFile(FILE * fp, int allowedLength){
	int curentLenth = getFileLength(fp);
	int count = 0;
	if(curentLenth > allowedLength){
		int skip = (curentLenth - allowedLength);
		char s[100];
		fp = fopen(".ussh_history", "r");
		FILE * fp2 = fopen(".temp_history", "w");
		if(fp != NULL){
			while(fgets(s,sizeof s,fp)!= NULL){
				count++;
				if(count > skip){
					fprintf(fp2, s);
				}
			}
			remove(".ussh_history");
			rename(".temp_history", ".ussh_history");
		}
	}
}

void printCWD(){
	char cwd[1000];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current Directory: %s\n", cwd);
	} else {
		perror("getcwd() error");
	}
}

void runCommand(Command * com){
	int status;
	pid_t pid = fork();
	char copy[100];
	strcpy(copy, com->argv[com->argc-1]);

	if(strcmp(copy, "&") == 0){
		if(pid == 0){
			setpgid(0, 0);
			com->argv[com->argc-1] = NULL;
			execvp(com->argv[0], com->argv);
			printf("Invalid Command\n");
			exit(-1);
		}
	}else{
		if(pid != 0){
			waitpid(pid, &status, 0);
		}else{
			execvp(com->argv[0], com->argv);
			printf("Invalid Command\n");
			exit(-1);
		}
	}
}

void readRC(FILE * fp, LinkedList * alias, int * HISTFILECOUNT, int * HISTCOUNT){
	fp = fopen(".usshrc", "r");
	int lineNum = 0;
	char s[100];
	char temp[100];
	if(fp != NULL){
		while(fgets(s,sizeof s,fp)!= NULL){
			lineNum++;
			if(lineNum == 1){
				strcpy(temp, s+10);
				*HISTCOUNT = atoi(temp);
			}else if(lineNum == 2){
				strcpy(temp, s+14);
				*HISTFILECOUNT = atoi(temp);
			}else if(lineNum == 4){
				addPath(s);
			}else if(lineNum >= 6){
				Alias * a = buildTypeAlias(s, 1);
				addLast(alias, buildNode_Type(a, 1), -1, cleanTypeAlias);
			}
		}
		fclose(fp);
	}
}

int containsRedirect(char *s)
{
	int i;
	for(i = 0; i < strlen(s); i++){
		if(s[i] == '<' || s[i] == '>'){
			return 0;
		}
	}
	return 1;
}// end containsPipe

void redirect(char ** argv)
{
	int n;
	pid_t pid = fork();
	if(pid == 0){
		int fd[2], in =0, out = 0;
		char input[100], output[100];
		for(int i=0;argv[i]!='\0';i++)
		{
			if(strcmp(argv[i],"<")==0)
			{
				argv[i]=NULL;
				strcpy(input,argv[i+1]);
				in=2;
			}

			if(strcmp(argv[i],">")==0)
			{
				argv[i]=NULL;
				strcpy(output,argv[i+1]);
				out=2;
			}

		}

		if(in)
		{
			if ((fd[0] = open(input, "r", 0)) < 0) {
				perror("Couldn't open input file");
				exit(0);
			}
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (out)
		{
			if ((fd[1] = open(output , "w", 1)) < 0) {
				perror("Couldn't open the output file");
				exit(0);
			}
			dup2(fd[1], 1);
			close(fd[1]);
		}

		execvp(argv[0], argv);
		perror("execvp");
		_exit(1);
	}else{
		waitpid(pid, &n, 0);
	}
}
