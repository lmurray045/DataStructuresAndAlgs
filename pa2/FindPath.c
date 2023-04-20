/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa2
* FindPath.c
* Main Program for finding paths 
* using BFS and Graph ADT
************************************************/

#include "List.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "ERROR: Invalid arguments passed. Please refer to guide for usage: \n\nRUN PROGRAM AS FOLLOWS: FindPath <input file> <output file>\n");
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
        addEdge(G, num1, num2);
    }
    printGraph(outfile, G);
    fprintf(outfile, "\n");
    List L = newList();
    while (fscanf(infile, "%d %d", &num1, &num2) != 0){
	    if (num1 == 0 || num2 == 0) {
	        break;
	    }
        BFS(G, num1);
        int sn = getDist(G, num2);
        if (sn == INF) {
            fprintf(outfile, "The distance from %d to %d is infinity\n", num1, num2);
            fprintf(outfile, "No %d-%d path exists\n", num1, num2);
            continue;
        }
        fprintf(outfile, "The distance from %d to %d is %d\n", num1, num2, sn);
        getPath(L, G, num2);
        fprintf(outfile, "A shortest %d-%d path is:", num1, num2);
        printList(outfile, L);
        fprintf(outfile, "\n");
        clear(L);
    }
    fclose(infile);
    fclose(outfile);
    freeGraph(&G);
    freeList(&L);
    return 0;
}

