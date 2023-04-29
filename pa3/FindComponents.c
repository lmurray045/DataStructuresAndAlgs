/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa3
* FindComponents.c
* Find Components Client Package
************************************************/
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "Graph.h"

int main(int argc, char * argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: Invalid arguments passed. Please refer to guide for usage: \n\nRUN PROGRAM AS FOLLOWS: FindComponents <input file> <output file>\n");
        exit(1);
    }      
    FILE * infile = fopen(argv[1], "r");
    FILE * outfile = fopen(argv[2], "w");
    int num1;
    int num2;
    fscanf(infile, "%d", &num1);
    Graph G = newGraph(num1);
    while (fscanf(infile, "%d %d", &num1, &num2) != 0){
	    if (num1 == 0 || num2 == 0) {
            break;
        }
        addArc(G, num1, num2);
    }
    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, G);
    fprintf(outfile, "\n");
    List L = newList();
    for (int i = 1; i <= getOrder(G); i++ ) {
        append(L, i);
    }
    Graph tG = transpose(G);
    DFS(G, L);
    DFS(tG, L);
    List roots = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        if (getParent(tG, i) == NIL) {
            append(roots, i);
        }
    }
    fprintf(outfile, "G contains %d strongly connected components:\n", length(roots));
    moveBack(L);
    moveFront(roots);
    List pL = newList();
    for (int i = 1; i <= length(roots); i++) {
        int cR = get(roots);
        fprintf(outfile, "Component %d:", i);
        int val = 0;
        while (val != cR) {
            int val = get(L);
            if (val == cR) {
                prepend(pL, val);
                movePrev(L);
                break;
            }
            else {
                append(pL, val);
                movePrev(L);
            }
        }
        printList(outfile, pL);
        clear(pL);
        moveNext(roots);
    }
    fclose(infile);
    fclose(outfile);
    freeGraph(&G);
    freeGraph(&tG);
    freeList(&roots);
    freeList(&pL);
    freeList(&L);
    return 0;
}
