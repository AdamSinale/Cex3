CC = gcc
AR = ar
OBJECTS_MAIN = Main.o
OBJECTS_LIB_MY_LIST = StrList.o
FLAGS = -Wall -g

all: myList.a StrList

myList.a:$(OBJECTS_LIB_MY_LIST)
	$(AR) -rcs myList.a $(OBJECTS_LIB_MY_LIST)

StrList: $(OBJECTS_MAIN) myList.a
	$(CC) $(FLAGS) -o StrList $(OBJECTS_MAIN) myList.a

StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c

clean:
	rm -f *.o *.a StrList