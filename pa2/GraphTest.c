/************************************************
* Liam Murray, lijamurr
* Spring 2023 CSE101 PA#2
* GraphTest.c
* Test Client for the Graph ADT
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
    printf("Adding edges...\n");
    addEdge(G, 2, 4);
    addEdge(G, 1, 5);
    addEdge(G, 3, 5);
    addEdge(G, 2, 5);
    printf("Current Graph representation: \n");
    printGraph(stdout, G);
    printf("\n\n\n");
    printf("Performing Breadth First Search on all points...\n");
    BFS(G, 1);
    printf("Source %d: Success\n", getSource(G));
    BFS(G, 2);
    printf("Source %d: Success\n", getSource(G));
    BFS(G, 3);
    printf("Source %d: Success\n", getSource(G));
    BFS(G, 4);
    printf("Source %d: Success\n", getSource(G));
    BFS(G, 5);
    printf("Source %d: Success\n", getSource(G));
    printf("\n\n\n");
    printf("Testing access functions: ");
    printf("Source: %d. Order: %d. Size: %d.\n", getSource(G), getOrder(G), getSize(G));
    printf("\n");
    for(int i = 1; i < 6; i++) {
        printf("Parent of %d: %d.\n", i, getParent(G, i));
        printf("Distance from %d to %d: %d\n", getSource(G), i, getDist(G, i));
    }
    printf("\n\n\n");
    printf("Testing Path function...\n");
    List L = newList();
    for (int i = 1; i < 6; i++) {
        getPath(L, G, i);
        printf("List Path for %d:", i);
        printList(stdout, L);
        clear(L);
    }
    printf("\n\n\n");
    printf("Testing Make Null...\n");
    makeNull(G);
    printGraph(stdout, G); 
    //printf("Source Vertex: %d\n", getSource(G));
    //int c = 4;
   // printf("parent of %d: %d\n", c, getParent(G, c));
    //printf("Distance from %d to %d: %d\n", getSource(G), c, getDist(G, c));
    freeGraph(&G);
    freeList(&L);
    printf("\n\n\n");
    printf("Test complete.\n");
    return 0;
}
