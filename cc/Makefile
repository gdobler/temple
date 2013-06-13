CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm
INCLUDES = -I/opt/local/include
LFLAGS = -L/opt/local/lib
LIBS = -lcfitsio

all:
	make readInput.o readData.o readMask.o readTemplates.o matrixMultiply.o temple.o temple

clean:
	rm *.o temple *~

readInput.o: tempFit.h
	${CC} ${CFLAGS} ${INCLUDES} -c readInput.cc

readData.o: tempFit.h
	${CC} ${CFLAGS} ${INCLUDES} -c readData.cc

readMask.o: tempFit.h
	${CC} ${CFLAGS} ${INCLUDES} -c readMask.cc

readTemplates.o: tempFit.h
	${CC} ${CFLAGS} ${INCLUDES} -c readTemplates.cc

matrixMultiply.o: tempFit.h
	${CC} ${CFLAGS} ${INCLUDES} -c matrixMultiply.cc

temple.o: tempFit.h
	${CC} ${CFLAGS} ${INCLUDES} -c temple.cc

temple: 
	${CC} ${CFLAGS} ${LFLAGS} ${LIBS} readInput.o readData.o readMask.o readTemplates.o matrixMultiply.o temple.o -o temple

