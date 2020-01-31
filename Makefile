CC = gcc 
# DEFINES = -DTEST_MODE
CFLAGS = -g -ggdb -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
PROG = mywc
PROG2 = avlMain


all: $(PROG) $(PROG2)

mywc: mywc.o
	$(CC) $(CFLAGS) -o mywc mywc.o 

#this is what you need to build, if these files have updates then rebuild
mywc.o: mywc.c 
# mywc.h
	$(CC) $(CFLAGS) -c mywc.c

avlMain: avlMain.o avlTree.o
	$(CC) $(CFLAGS) -o avlMain avlMain.o avlTree.o 

avlMain.o: avlMain.c avlTree.h
	$(CC) $(CFLAGS) -c avlMain.c

avlTree.o: avlTree.c avlTree.h
	$(CC) $(CFLAGS) -c avlTree.c

clean:
	rm -f $(PROG) *.o *~ \#*