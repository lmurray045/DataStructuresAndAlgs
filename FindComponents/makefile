#------------------------------------------------------------------------------
# Liam Murray, lijamurr
# CSE101 Spring 2023, Pa2
# FindComponents.c
# Makefile for Find Components program
# Commands:
#  # make             makes FindComponents and GraphTest
#  # make clean       removes object files
#  # make check       runs valgrind to check for memory errors requires: "infile" 
#  #	    		  and "outfile"
#  # make GraphTest   makes Graph test file
#  #------------------------------------------------------------------------------

FindComponents : GraphTest.o FindComponents.o List.o Graph.o
	gcc -std=c17 -Wall -o FindComponents FindComponents.o List.o Graph.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o List.o Graph.o

GraphTest : GraphTest.o List.o Graph.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o List.o Graph.o

GraphTest.o : List.h Graph.h GraphTest.c
	gcc -std=c17 -Wall -c GraphTest.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c List.c

Graph.o : Graph.h Graph.c
	gcc -std=c17 -Wall -c Graph.c

FindComponents.o : List.h Graph.h FindComponents.c List.c Graph.c
	gcc -std=c17 -Wall -c FindComponents.c

clean :
	rm -f FindComponents GraphTest FindComponents.o GraphTest.o List.o Graph.o

check : FindComponents infile outfile
	valgrind --leak-check=full FindComponents infile outfile
