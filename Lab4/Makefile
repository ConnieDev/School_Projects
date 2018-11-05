all:	lab4

lab4:	cscd340Lab4.c ./tokenize/tokenize.o ./utils/myUtils.o
	gcc -g cscd340Lab4.c ./tokenize/tokenize.o ./utils/myUtils.o -o lab4

tokenize.o:	./tokenize/tokenize.c ./tokenize/tokenize.h
	gcc -g -c ./tokenize/tokenize.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
		gcc -g -c ./utils/myUtils.c

clean:
	rm ./utils/myUtils.o
	rm ./tokenize/tokenize.o
	rm lab4

