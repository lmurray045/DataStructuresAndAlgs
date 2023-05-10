/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa4
* Matrix.c
* Functions and code for the Matrix ADT
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

//entry function definition

typedef struct EntryObj {
    int col;
    double data;
} EntryObj;

//this is saying that the type "Entry" is now an alias for EntryObj Pointers
typedef EntryObj* Entry;

//Entry contructor
Entry newEntry(int c, double d) {
    Entry en = (Entry)malloc(sizeof(EntryObj));
    en->col = c;
    en->data = d;
    return en;
}

void freeEntry(Entry *pE) {
    free(*pE);
    *pE = NULL;
    pE = NULL;
    return;
}

void printEntry(FILE *fp, Entry E) {
    fprintf(fp, " (%d, %.1lf)", E->col, E->data);
    return;
}

int entry_equals(Entry A, Entry B) {
    if(A == NULL || B == NULL) {
        fprintf(stderr, "ERROR: in entry_equals(); entry passed not valid.\n");
        exit(1);
    }
    if (A->data == B->data && A->col == B->col) {
        return 1;
    }
    return 0;
}

typedef struct MatrixObj {
    List * rows;
    int size;
    int NNZ;
} MatrixObj;

typedef MatrixObj* Matrix;

//constructor and deconstructor
Matrix newMatrix(int n) {
    Matrix M = (Matrix)malloc(sizeof(MatrixObj));
    M->rows = (List *)calloc((n+1), sizeof(List));
    for (int i = 1; i < (n+1); i++){
        M->rows[i] = newList();
    }
    M->size = n;
    M->NNZ = 0;
    return M;
}

void freeMatrix(Matrix * pM) {
    if (pM == NULL) {
        fprintf(stderr, "ERROR: In freeMatrix(): passed pointer is NULL.\n");
        exit(1);
    }
    for (int i = 1; i < ((*pM)->size + 1); i++) {
        moveFront((*pM)->rows[i]);
        for (int j = 0; j < length((*pM)->rows[i]); j++) {
            Entry E = (Entry)get((*pM)->rows[i]);
            freeEntry(&E);
            moveNext((*pM)->rows[i]);
            E = NULL;
        }
        freeList(&((*pM)->rows[i]));
    }
    free((*pM)->rows);
    free(*pM);
    *pM = NULL;
    return;
}

//Misc Helper functions
double vectorDot(List P, List Q, int size) {
    double total = 0;
    moveFront(P);
    moveFront(Q);
    double aE, bE;
    int caE, cbE;
    for (int n = 1; n <= size; n++) {
        if (index(P) == -1) {
            caE = -1;
        }
        else {
            caE = ((Entry)get(P))->col;
        }
        if (index(Q) == -1) {
            cbE = -1;
        }
        else {
            cbE = ((Entry)get(Q))->col;
        }
        aE = 0;
        bE = 0;
        if (caE == n) {
            aE = ((Entry)get(P))->data;
            moveNext(P);
        }
        if (cbE == n) {
            bE = ((Entry)get(Q))->data;
            moveNext(Q);
        }
        total += (aE * bE);
    }
    return total;
}

//access functions
int size(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "ERROR: in size(); Matrix passed is NULL.\n");
        exit(1);
    }
    return M->size;
}

int NNZ(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "ERROR: in size(); Matrix passed is NULL.\n");
        exit(1);
    }
    return M->NNZ;
}

int equals(Matrix A, Matrix B) {
    if (A == NULL) {
        fprintf(stderr, "ERROR: in equals(); Matrix A is NULL.\n");
        exit(1);
    }
    if (B == NULL) {
        fprintf(stderr, "ERROR: in equals(); Matrix B is NULL.\n");
        exit(1);
    }
    if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
        return 0;
    }
    for (int i = 1; i <= size(A); i++) {
        if (length(A->rows[i]) != length(B->rows[i])) {
            return 0;
        }
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        for(int j = 0; j < length(A->rows[i]); j++) {
            Entry aE = (Entry)get(A->rows[i]);
            Entry bE = (Entry)get(B->rows[i]);
            if (entry_equals(aE, bE) != 1) {
                return 0;
            }
            moveNext(A->rows[i]);
            moveNext(B->rows[i]);
        }
    }
    return 1;
}

// manipulations functions
void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "ERROR: in makeZero(); Matrix passed is NULL.\n");
        exit(1);
    }
    for (int i = 1; i <= size(M); i++) {
        moveFront(M->rows[i]);
        for(int j = 0; j < length(M->rows[i]); j++) {
            Entry aE = (Entry)get(M->rows[i]);
            freeEntry(&aE);
            moveNext(M->rows[i]);
        }
        clear(M->rows[i]);
    }
    M->NNZ = 0;
    return;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "ERROR: in changeEntry(); Matrix passed is NULL.\n");
        exit(1);
    } 
    if (i < 1 || i > size(M)) {
        fprintf(stderr, "ERROR: in changeEntry(); I is out of range.\n");
        exit(1);
    }
    if (j < 1 || j > size(M)) {
        fprintf(stderr, "ERROR: in changeEntry(); J is out of range.\n");
        exit(1);
    }
    moveFront(M->rows[i]);
    if (length(M->rows[i]) == 0) {
	if (x == 0) {
	   return;
	}
        Entry E = newEntry(j, x);
        append(M->rows[i], E);
        M->NNZ += 1;
        return;
    }
    else {
	moveFront(M->rows[i]);
        for (int n = 1; n <= length(M->rows[i]); n++) {
            Entry cE = get(M->rows[i]);
            if (cE->col == j) {
		if (x == 0){
		    delete(M->rows[i]);
		    M->NNZ -= 1;
		    return;	
		}
                cE->data = x;
                return;
            }
            else if (cE->col > j) {
                if (x == 0){
                    return;
		}
		Entry E = newEntry(j, x);
                insertBefore(M->rows[i], E);
                M->NNZ += 1;
                return;
            } 
            else {
                moveNext(M->rows[i]);
            }
	}
	if (x == 0){
             return;
        }
        Entry E = newEntry(j, x);
        append(M->rows[i], E);
        M->NNZ += 1;
        return;
    }
}

//arithmetic functions

Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "ERROR in copy(); Matrix passed is NULL.\n");
        exit(1);
    }
    Matrix B = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        for (int n = 1; n <= length(A->rows[i]); n++) {
            double num = ((Entry)get(A->rows[i]))->data;
            changeEntry(B, i, n, num);
            moveNext(A->rows[i]);
        }
    }
    return B;
}

Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "ERROR in transpose(); Matrix passed is NULL.\n");
        exit(1);
    }
    Matrix B = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        for (int n = 1; n <= length(A->rows[i]); n++) {
            float num = ((Entry)get(A->rows[i]))->data;
	    int col1 = ((Entry)get(A->rows[i]))->col;
            changeEntry(B, col1, i, num);
            moveNext(A->rows[i]);
        }
    }
    return B;
}


Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "ERROR in scalarMult(); Matrix passed is NULL.\n");
        exit(1);
    }
    Matrix B = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        for (int n = 1; n <= length(A->rows[i]); n++) {
            double num = ((Entry)get(A->rows[i]))->data;
	    int col1 = ((Entry)get(A->rows[i]))->col;
            changeEntry(B, i, col1, (num * x));
            moveNext(A->rows[i]);
        }
    }
    return B;
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "ERROR in sum(); a Matrix passed is NULL.\n");
        exit(1);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "ERROR in sum(); Matrix dimensions are not equal.\n");
        exit(1);
    }
    if (A == B || equals(A, B) == 1) {
        return scalarMult(2, A);
    }
    Matrix C = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        double aE, bE;
        int caE, cbE;
        for (int n = 1; n <= size(A); n++) {
            if (index(A->rows[i]) == -1) {
                caE = -1;
            }
            else {
                caE = ((Entry)get(A->rows[i]))->col;
            }
            if (index(B->rows[i]) == -1) {
                cbE = -1;
            }
            else {
                cbE = ((Entry)get(B->rows[i]))->col;
            }
            aE = 0;
            bE = 0;
            if (caE == n) {
                aE = ((Entry)get(A->rows[i]))->data;
                moveNext(A->rows[i]);
            }
            if (cbE == n) {
                bE = ((Entry)get(B->rows[i]))->data;
                moveNext(B->rows[i]);
            }
            if (aE == 0 && bE == 0) {
                continue;
            }
            changeEntry(C, i, n, (aE + bE));
        }
    }
    return C;
}

Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "ERROR in diff(); a Matrix passed is NULL.\n");
        exit(1);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "ERROR in diff(); Matrix dimensions are not equal.\n");
        exit(1);
    }
    Matrix C = newMatrix(size(A));
    if (A == B || equals(A, B) == 1) {
        return C;
    }
    for(int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        double aE, bE;
        int caE, cbE;
        for (int n = 1; n <= size(A); n++) {
            if (index(A->rows[i]) == -1) {
                caE = -1;
            }
            else {
                caE = ((Entry)get(A->rows[i]))->col;
            }
            if (index(B->rows[i]) == -1) {
                cbE = -1;
            }
            else {
                cbE = ((Entry)get(B->rows[i]))->col;
            }
            aE = 0;
            bE = 0;
            if (caE == n) {
                aE = ((Entry)get(A->rows[i]))->data;
                moveNext(A->rows[i]);
            }
            if (cbE == n) {
                bE = ((Entry)get(B->rows[i]))->data;
                moveNext(B->rows[i]);
            }
            if (aE == 0 && bE == 0) {
                continue;
            }
            changeEntry(C, i, n, (aE - bE));
        }
    }
    return C;
}

void printMatrix();

Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "ERROR in product(); a Matrix passed is NULL.\n");
        exit(1);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "ERROR in product(); Matrix dimensions are not equal.\n");
        exit(1);
    }
    Matrix tB = transpose(B);
    Matrix C = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        for (int j = 1; j <= size(A); j++) {
            changeEntry(C, i, j, vectorDot(A->rows[i], tB->rows[j], size(A)));
        }
    }
    freeMatrix(&tB);
    return C;
}

//other operations
void printMatrix(FILE * out, Matrix M) {
    for (int i = 1; i <= size(M); i++) {
         if (length(M->rows[i]) == 0) {
            continue;
         }
	 fprintf(out, "%d:", i);
        moveFront(M->rows[i]);
        for (int j = 0; j < length(M->rows[i]); j++) {
            printEntry(out, ((Entry)(get(M->rows[i]))));
            moveNext(M->rows[i]);
        }
        fprintf(out, "\n");
    }
    return;
}

/*
int main(void) {
    Entry E = newEntry(4, 5.0);
    printEntry(stdout, E);
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

    freeEntry(&E);
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
*/
