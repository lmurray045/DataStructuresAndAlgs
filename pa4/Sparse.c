/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa4
* Sparse.c
* Sparse Client for the Matrix ADT
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"

int main(int argc, char * argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: Invalid arguments passed. Please refer to guide for usage: \n\nRUN PROGRAM AS FOLLOWS: FindComponents <input file> <output file>\n");
        exit(1);
    }      
    FILE * infile = fopen(argv[1], "r");
    FILE * outfile = fopen(argv[2], "w");
    int n, a, b, num1, num2;
    double num3;
    fscanf(infile, "%d %d %d", &n, &a, &b);
    //fscanf(infile, "%c", &nl);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    for (int i = 0; i < a; i++){
        fscanf(infile, "%d %d %.17g", &num1, &num2, &num3);
        if (num3 == 0) {
               continue;
        }
	changeEntry(A, num1, num2, num3);
    }
    for (int j = 0; j < b; j++){
        fscanf(infile, "%d %d %lf", &num1, &num2, &num3);
        if (num3 == 0) {
		continue;
	}
	changeEntry(B, num1, num2, num3);
    }
    fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outfile, A);
    fprintf(outfile, "\n");
    fprintf(outfile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");
    
    Matrix sA = scalarMult(1.5, A);
    fprintf(outfile, "(1.5)*A =\n");
    printMatrix(outfile, sA);
    fprintf(outfile, "\n");

    Matrix bA = sum(A, B);
    fprintf(outfile, "A+B =\n");
    printMatrix(outfile, bA);
    fprintf(outfile, "\n");

    Matrix aA = sum(A, A);
    fprintf(outfile, "A+A =\n");
    printMatrix(outfile, aA);
    fprintf(outfile, "\n");

    Matrix Ba = diff(B, A);
    fprintf(outfile, "B-A =\n");
    printMatrix(outfile, Ba);
    fprintf(outfile, "\n");

    Matrix Aa = diff(A, A);
    fprintf(outfile, "A-A =\n");
    printMatrix(outfile, Aa);
    fprintf(outfile, "\n");

    Matrix tA = transpose(A);
    fprintf(outfile, "Transpose(A) =\n");
    printMatrix(outfile, tA);
    fprintf(outfile, "\n");

    Matrix AmB = product(A, B);
    fprintf(outfile, "A*B =\n");
    printMatrix(outfile, AmB);
    fprintf(outfile, "\n");

    Matrix BmB = product(B, B);
    fprintf(outfile, "B*B =\n");
    printMatrix(outfile, BmB);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&sA);
    freeMatrix(&bA);
    freeMatrix(&aA);
    freeMatrix(&Ba);
    freeMatrix(&Aa);
    freeMatrix(&tA);
    freeMatrix(&AmB);
    freeMatrix(&BmB);
    return 0;
}
