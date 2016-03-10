
CC = gcc
OBJS = timer.o
FLAGS = -fopenmp -O3
SEQFLAGS = -O3 
DEBUGFLAGS = -g

EXEC = knapSeq knapOMP knapBlock knapBP

all: $(EXEC)

knapSeq: knapSeq.c timer.o
	$(CC)  $(SEQFLAGS) $(DEBUGFLAGS) -o knapSeq knapSeq.c $(OBJS) 

knapOMP: knapOMP.c timer.o
	$(CC) $(FLAGS) $(DEBUGFLAGS) -o $@ $< $(OBJS)

knapBlock: knapBlock.c timer.o
	$(CC) $(SEQFLAGS) -o $@ $< $(OBJS)

knapBP: knapBP.c timer.o
	$(CC) $(FLAGS) -o $@ $< $(OBJS)

timer.o: timer.c
	$(CC) -o $@ -c timer.c

clean:
	rm -f $(EXEC) $(OBJS)
