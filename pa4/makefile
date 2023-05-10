#------------------------------------------------------------------------------
# Liam Murray, lijamurr
# CSE101 Spring 2023, Pa4
# Sparse.c
# Makefile for Sparse program
# Commands:
#  # make             makes Sparce and MatrixTest
#  # make clean       removes object files
#  # make check       runs valgrind to check for memory errors requires: "infile" 
#  #	    		  and "outfile"
#  # make MatrixTest  makes Matrix test file
#  #------------------------------------------------------------------------------

Sparse : Sparse.o List.o Matrix.o
	gcc -std=c17 -Wall -o Sparse Sparse.o List.o Matrix.o

MatrixTest : MatrixTest.o List.o Matrix.o
	gcc -std=c17 -Wall -o MatrixTest MatrixTest.o List.o Matrix.o

MatrixTest.o : List.h Matrix.h MatrixTest.c
	gcc -std=c17 -Wall -c MatrixTest.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c List.c

Matrix.o : Matrix.h Matrix.c
	gcc -std=c17 -Wall -c Matrix.c

Sparse.o : List.h Matrix.h Sparse.c List.c Matrix.c
	gcc -std=c17 -Wall -c Sparse.c

clean :
	rm -f Sparse MatrixTest Sparse.o MatrixTest.o List.o Matrix.o

check : Sparse infile outfile
	valgrind --leak-check=full Sparse infile outfile
