#------------------------------------------------------------------------------
# Liam Murray
# CSE 101, Spring 2023, Pa6
#  Makefile for List ADT
#
#  make             makes Shuffle and ListTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

COMPILE          = g++ -std=c++17 -Wall -c 
LINK             = g++ -std=c++17 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full

Shuffle : ListTest List.o Shuffle.o
	$(LINK) Shuffle Shuffle.o List.o 

ListTest : ListTest.o List.o
	$(LINK) ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	$(COMPILE) ListTest.cpp 

List.o : List.h List.cpp
	$(COMPILE) List.cpp

clean :
	$(REMOVE) ListTest Shuffle ListTest.o List.o Shuffle.o 

check : Shuffle 
	$(MEMCHECK) Shuffle 35