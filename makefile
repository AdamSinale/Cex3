
CC = gcc
FLAGS = -Wall -g

AR = ar
OBJECTS_MAIN = Main.o
OBJECTS_FUNCTIONS = StrList.o
HEADER = StrList.h

all: functions StrList

functions: StrList.a

StrList.a: $(OBJECTS_FUNCTIONS)
	$(AR) rcs $@ $^
	
StrList: $(OBJECTS_MAIN) StrList.a
	$(CC) $(FLAGS) -o $@ $^

Main.o: Main.c $(HEADER)
	$(CC) $(FLAGS) -c $<
StrList.o: StrList.c $(HEADER)
	$(CC) $(FLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.a StrList
