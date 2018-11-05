all:	ussh

ussh:	cscd340lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/listUtils.o ./linkedlist/linkedList.o ./aliases/alias.o ./command/command.o
	gcc -g cscd340lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./linkedlist/listUtils.o ./linkedlist/linkedList.o ./pipes/pipes.o ./aliases/alias.o ./command/command.o -o ussh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

listUtils.o:	./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc -g -c ./linkedlist/listUtils.c

linkedList.o:	./linkedlist/linkedList.h ./linkedlist/linkedList.c ./linkedlist/requiredIncludes.h
	gcc -g -c ./linkedlist/linkedList.c
	
command.o:			./command/command.c ./command/command.h
	gcc -g -c ./command/command.c
	
alias.o:			./aliases/alias.c ./aliases/alias.h
	gcc -g -c ./aliases/alias.c
	
process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./linkedlist/*.o
	rm ./command/command.o
	rm ussh

