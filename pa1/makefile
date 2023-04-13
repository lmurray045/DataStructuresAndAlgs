#------------------------------------------------------------------------------
#  Makefile for Lex program
#  #
#  make             makes Lex
#  #  make clean       removes object files
#  make check       runs valgrind to check for memory errors requires: "infile" 
#  		    and "outfile"
#  #  make testList    makes List test file
#  #------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o 

testList : testList.o List.o
	gcc -std=c17 -Wall -o testList testList.o List.o 

testList.o : List.h testList.c
	gcc -std=c17 -Wall -c testList.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c List.c

Lex.o : List.h Lex.c List.c
	gcc -std=c17 -Wall -c Lex.c

clean :
	rm -f Lex testList Lex.o testList.o List.o

check : Lex infile outfile
	valgrind --leak-check=full Lex infile outfile
