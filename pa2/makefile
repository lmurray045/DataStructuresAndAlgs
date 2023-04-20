#------------------------------------------------------------------------------
# Liam Murray, lijamurr
# CSE101 Spring 2023, Pa2
# FindPath.c
# Makefile for Lex program
# Commands:
#  # make             makes FindPath
#  # make clean       removes object files
#  # make check       runs valgrind to check for memory errors requires: "infile" 
#  #	    		  and "outfile"
#  # make GraphTest   makes Graph test file
#  #------------------------------------------------------------------------------

FindPath : FindPath.o List.o Graph.o
	gcc -std=c17 -Wall -o FindPath FindPath.o List.o Graph.o

GraphTest : GraphTest.o List.o Graph.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o List.o Graph.o

GraphTest.o : List.h Graph.h GraphTest.c
	gcc -std=c17 -Wall -c GraphTest.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c List.c

Graph.o : Graph.h Graph.c
	gcc -std=c17 -Wall -c Graph.c

FindPath.o : List.h Graph.h FindPath.c List.c Graph.c
	gcc -std=c17 -Wall -c FindPath.c

clean :
	rm -f FindPath GraphTest FindPath.o GraphTest.o List.o Graph.o

check : FindPath infile outfile
	valgrind --leak-check=full FindPath infile outfile
