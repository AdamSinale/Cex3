CC=gcc
AR=ar
FLAGS= -Wall -g

all:  StrList

# Rule to build the library 'libStrList.a'
libStrList.a: StrList.o
	ar rcs libStrList.a StrList.o

# Rule to compile my_graph.c into an object file
StrList.o: StrList.c StrList.h 
	$(CC) $(FLAGS) -c StrList.c -fPIC

 #Rule to compile Main.c into an object file
Main.o: Main.c StrList.h
	$(CC) $(FLAGS) -c Main.c -o Main.o

# Rule to link the executable with the library
StrList: Main.o libStrList.a
	$(CC) $(FLAGS) Main.o -L. -lStrList -o StrList

.PHONY: clean all

clean: 
	rm -f *.o *.a *.so StrList