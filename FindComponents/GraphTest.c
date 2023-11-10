/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa3
* GraphTest.c
* Test Cases for the Graph ADT
************************************************/
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "Graph.h"


int main(void) {
    printf("Testing graph creation...\n");
    Graph G = newGraph(5);
    printf("Adding arcs...\n");
    addArc(G, 2, 4);
    addArc(G, 1, 5);
    addArc(G, 3, 5);
    addArc(G, 2, 5);
    printf("Current Graph representation: \n");
    printGraph(stdout, G);
    printf("\n\n\n");
    printf("Performing Depth First Search on generated Graph...\n");
    List dL = newList();
    for (int i = 1; i <= 5; i++) {
        append(dL, i);
    }
    DFS(G, dL);
    printf("\n\n\n");
    printf("Testing access functions: ");
    printf("Order: %d. Size: %d.\n", getOrder(G), getSize(G));
    printf("\n");
    for(int i = 1; i < 6; i++) {
        printf("Parent of %d: %d.\n", i, getParent(G, i));
        printf("Discover time of %d: %d; Finish time of %d: %d\n", i, getDiscover(G, i), i, getFinish(G, i));
    }
    printf("\n\n\n");
    printf("Testing Copy function...\n");
    Graph cG = copyGraph(G);
    printf("copied Graph:\n");
    printGraph(stdout, cG);
    printf("\n\n\n");
    printf("Testing transpose function...\n");
    Graph tG = transpose(G);
    printf("transposed Graph:\n");
    printGraph(stdout, tG);
    printf("\n\n\n");
    printf("Testing Make Null...\n");
    makeNull(G);
    printGraph(stdout, G); 
    //printf("Source Vertex: %d\n", getSource(G));
    //int c = 4;
    //printf("parent of %d: %d\n", c, getParent(G, c));
    //printf("Distance from %d to %d: %d\n", getSource(G), c, getDist(G, c));
    freeGraph(&G);
    freeList(&dL);
    freeGraph(&cG);
    freeGraph(&tG);
    printf("\n\n\n");
    printf("Test complete.\n");
    return 0;
                                           }
    
