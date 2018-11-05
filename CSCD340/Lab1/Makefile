CC = gcc

FLAGS = -c -g -m32

OBJS = ./utils/fileUtils.o ./stock/stock.o ./utils/myUtils.o ./genericArray/genericArray.o

MAIN = cscd340Lab1.c

EXE = ./lab1

all:	lab1


lab1:	${OBJS} ${MAIN}
	${CC} -g ${OBJS} ${MAIN} -o ${EXE}


stock.o:	./stock/stock.c ./stock/stock.h
	${CC} ${FLAGS} lab1.c


fileUitls.o:	./utils/fileUtils.c ./utils/fileUtils.h
	${CC} ${FLAGS} fileUtil.c


myUtils.o:	./utils/myUtils.c ./utils/myUtils.h
	${CC} ${FLAGS} myUtil.c


genericArray.o:	./genericArray/genericArray.c ./genericArray/genericArray.f
	${CC} ${FLAGS} ./genericArray/genericArray.c

clean:
	rm -rf ./stock/*.o
	rm -rf ./utils/*.o
	rm -rf ./genericArray/*.o
	rm -rf lab1
