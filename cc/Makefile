CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm
INCLUDES = -I/opt/local/include
LFLAGS = -L/opt/local/lib
LIBS = -lcfitsio

all:
	make readInput.o readData.o readMask.o readTemplates.o matrixMultiply.o matrixInvert.o temple.o temple

clean:
	rm *.o temple *~

readInput.o: temple.h
	${CC} ${CFLAGS} ${INCLUDES} -c readInput.cc

readData.o: temple.h
	${CC} ${CFLAGS} ${INCLUDES} -c readData.cc

readMask.o: temple.h
	${CC} ${CFLAGS} ${INCLUDES} -c readMask.cc

readTemplates.o: temple.h
	${CC} ${CFLAGS} ${INCLUDES} -c readTemplates.cc

matrixMultiply.o: temple.h
	${CC} ${CFLAGS} ${INCLUDES} -c matrixMultiply.cc

matrixInvert.o: temple.h
	${CC} ${CFLAGS} ${INCLUDES} -c matrixInvert.cc

temple.o: temple.h
	${CC} ${CFLAGS} ${INCLUDES} -c temple.cc

temple: 
	${CC} ${CFLAGS} ${LFLAGS} ${LIBS} readInput.o readData.o readMask.o readTemplates.o matrixMultiply.o matrixInvert.o temple.o -o temple
