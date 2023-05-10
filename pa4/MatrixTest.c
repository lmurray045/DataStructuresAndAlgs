/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa4
* MatrixTest.c
* Test Harness for the Matrix ADT
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

int main(void) {
    printf("Beginning Matrix Tests...\n");
    printf("\n");
    printf("\n");
    Matrix M = newMatrix(3);
    changeEntry(M, 3, 2, 5.00);
    changeEntry(M, 2, 1, 6.00);
    changeEntry(M, 1, 3, 7.50);
    changeEntry(M, 3, 1, 99.00);
    changeEntry(M, 3, 3, 56.00);
    changeEntry(M, 2, 2, 2.00);
    printMatrix(stdout, M);
    Matrix M2 = newMatrix(3);
    changeEntry(M2, 3, 2, 5.00);
    changeEntry(M2, 2, 1, 6.00);
    changeEntry(M2, 1, 3, 7.50);
    changeEntry(M2, 3, 1, 99.00);
    changeEntry(M2, 3, 3, 56.00);
    changeEntry(M2, 2, 2, 2.00);


    printf("Non-Zero elements: %d\n", NNZ(M2));
    printMatrix(stdout, M2);
    printf("M and M2 equality: %d\n\n", equals(M, M2));
    printf("Matrix cleared\n\n");
    makeZero(M2);
    printf("Non-Zero elements: %d\n", NNZ(M2));
    printMatrix(stdout, M2);
    

    printf("\n\n");
    printf("Copying Matrix\n");
    Matrix M3 = copy(M);
    printf("Non-Zero elements of M3: %d\n", NNZ(M3));
    printMatrix(stdout, M3);

    printf("\n\n");
    printf("Transposing Matrix\n");
    Matrix M4 = transpose(M);
    printf("Non-Zero elements of M4: %d\n", NNZ(M4));
    printMatrix(stdout, M4);

    printf("\n\n");
    printf("Scaling Matrix by 4\n");
    Matrix M5 = scalarMult(4, M);
    printf("Non-Zero elements of M5: %d\n", NNZ(M5));
    printMatrix(stdout, M5);

    printf("\n\n");
    printf("A + B\n");
    Matrix M6 = sum(M3, M5);
    printf("Non-Zero elements of M6: %d\n", NNZ(M6));
    printMatrix(stdout, M6);

    printf("\n\n");
    printf("B - B\n");
    Matrix M7 = diff(M5, M5);
    printf("Non-Zero elements of M5: %d\n", NNZ(M7));
    printMatrix(stdout, M7);

    printf("\n\n");
    printf("product of A and B\n");
    Matrix M8 = product(M3, M5);
    printf("Non-Zero elements of M5: %d\n", NNZ(M8));
    printMatrix(stdout, M8);
 
    Matrix A = newMatrix(3);
    Matrix B = newMatrix(3);   
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 3);
    changeEntry(A, 2, 1, 4);
    changeEntry(A, 2, 2, 5);
    changeEntry(A, 2, 3, 6);
    changeEntry(A, 3, 1, 7);
    changeEntry(A, 3, 2, 8);
    changeEntry(A, 3, 3, 9);

    changeEntry(B, 1, 1, 1);
    changeEntry(B, 2, 2, 1);
	
    Matrix pA = product(A, B);

    printf("Matrix A * B: \n");
    printMatrix(stdout, pA);
	
    freeMatrix(&M);
    freeMatrix(&M2);
    freeMatrix(&M3);
    freeMatrix(&M4);
    freeMatrix(&M5);
    freeMatrix(&M6);
    freeMatrix(&M7);
    freeMatrix(&M8);
    return 0;
}
