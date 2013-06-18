CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm
INCLUDES = -I/opt/local/include
LFLAGS = -L/opt/local/lib
LIBS = -lcfitsio
SRCS = readInput.cc readData.cc readMask.cc readTemplates.cc matrixMultiply.cc matrixInvert.cc genILC.cc temple.cc
OBJS = $(SRCS:.cc=.o)
MAIN = temple

.PHONY: depend clean

all: $(MAIN)
	@echo temple executable compiled...

$(MAIN): $(OBJS)
	$(CC) $(CLFAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
