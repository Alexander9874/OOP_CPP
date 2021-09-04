CC=g++

CFLAGS= -Wall -Wextra -Werror

-c=-c

ALL=*.cpp

all:
	g++ -Wall -Wextra -Werror First_File.cpp
print:
	cat First_File.cpp
flag:
	$(CC) $(CFLAGS) First_File.cpp
multiple:
	$(CC) $(CFLAGS) *.cpp
via_objects: objects
	$(CC) *.o
objects:
	$(CC) $(-c) $(ALL)
