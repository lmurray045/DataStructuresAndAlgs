/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa2
* Graph.c
* Functions and code for the Graph ADT
************************************************/
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "Graph.h"

#define INF -1
#define NIL 0

typedef struct GraphObj {
    List * vertices;
    //COLOR CODES: 0 == white, 1 == gray, 2 == black
    int * color;
    int * parent;
    int * distance;
    int order;
    int size;
    int last;
} GraphObj;

typedef GraphObj* Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n) {
    Graph G = (Graph)malloc(sizeof(GraphObj));
    if (G == NULL) {
        fprintf(stderr, "ERROR: in newGraph(); malloc failed.\n");
        exit(1);
    }
    G->vertices = (List *)calloc((n+1), sizeof(List));
    for (int i = 1; i < (n+1); i++){
        G->vertices[i] = newList();
    }
    G->color = (int *)calloc((n+1), sizeof(int));
    G->parent = (int *)calloc((n+1), sizeof(int));
    G->distance = (int *)calloc((n+1), sizeof(int));
    for (int i = 1; i < (n+1); i++){
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->order = n;
    G->size = 0;
    G->last = NIL;
    return G;
}

void freeGraph (Graph * pG) {
    if (pG == NULL) {
        fprintf(stderr, "ERROR: In freeGraph(): passed pointer is NULL.\n");
        exit(1);
    }
    for (int i = 1; i < ((*pG)->order + 1); i++) {
        freeList(&((*pG)->vertices[i]));
    }
    free((*pG)->vertices);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free(*pG);
    *pG = NULL;
    return;
}


/*** Access functions ***/
int getOrder (Graph G) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getOrder(): Graph passed is NULL.\n");
        exit(1);
    }
    return G->order;
}

int getSize (Graph G) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getSize(): Graph passed is NULL.\n");
        exit(1);
    }
    return G->size;
}

int getSource (Graph G) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getSource(): Graph passed is NULL.\n");
        exit(1);
    }
    return G->last;
}

int getParent (Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getParent(): Graph passed is NULL.\n");
        exit(1);
    }
    if (u <= 0 || u > getOrder(G)) {
        fprintf(stderr, "ERROR: in getParent(): u is not in range.\n");
        exit(1);
    }
    if (G->last == NIL) {
        return NIL;
    }
    return G->parent[u];
}

int getDist (Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getDist(): Graph passed is NULL.\n");
        exit(1);
    }
    if (u <= 0 || u > getOrder(G)) {
        fprintf(stderr, "ERROR: in getParent(): u is not in range.\n");
        exit(1);
    }
    if (G->last == NIL) {
        return INF;
    }
    return G->distance[u];
}

void getPath (List L, Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getPath(): Graph passed is NULL.\n");
        exit(1);
    }
    if (G->last == NIL) {
        fprintf(stderr, "ERROR: in getPath(): No valid source, make sure BFS() is called.\n");
        exit(1);
    }
    if (length(L) == 0) {
        prepend(L, u);
    }
    if (u == G->last) {
        return;
    }
    else if (G->parent[u] == NIL) {
        prepend(L, NIL);
        return;
    }
    else {
        prepend(L, G->parent[u]);
        getPath(L, G, G->parent[u]);
        return;
    }
}

/*** Manipulation Functions ***/

void BFS(Graph G, int s){
    if (G == NULL) {
        fprintf(stderr, "ERROR: in BFS(): Graph passed is NULL.\n");
        exit(1);
    }
    if (s < 1 || s > G->order) {
        fprintf(stderr, "ERROR: in BFS(): Source is out of range.\n");
        exit(1);
    }
    G->last = s;
    List Q = newList();
    for (int i = 1; i < G->order+1; i++) {
        G->color[i] = 0;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = 0;
    G->distance[s] = 0;
    append(Q, s);
    while(length(Q) != 0) {
        int x = front(Q);
        deleteFront(Q);
        moveFront(Q);
        moveFront(G->vertices[x]);
        for (int j = 0; j < length(G->vertices[x]); j++) {
            int y = get(G->vertices[x]);
            moveNext(G->vertices[x]);
            if (G->color[y] == 0) {
                G->color[y] = 1;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q, y);
            }
        }
        G->color[x] = 2;
    }
    freeList(&Q);  
}

void makeNull (Graph G) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in makeNull(); graph passed is NULL.\n");
        exit(1);
    }
    for (int i = 1; i < (G->order + 1); i++) {
        clear(G->vertices[i]);
    }
    return;
}

void addArc (Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in addArc(); graph passed is NULL.\n");
        exit(1);
    }
    if (u <= 0 || u > getOrder(G)) {
        fprintf(stderr, "ERROR: in addArc(); u argument is not in valid range.\n");
        exit(1);
    }
    if (v <= 0 || v > getOrder(G)) {
        fprintf(stderr, "ERROR: in addArc(); v argument is not in valid range.\n");
        exit(1);
    }
    if (length(G->vertices[u]) == 0){
        append(G->vertices[u], v);
        G->size += 1;
        return;
    }
    int ins = v;
    moveFront(G->vertices[u]);
    while (ins > get(G->vertices[u])) {
        moveNext(G->vertices[u]);
        if (index(G->vertices[u]) < 0) {
            append((G->vertices[u]), v);
            G->size += 1;
            return;
        }
    }
    insertBefore(G->vertices[u], v);
    G->size += 1;
    return;
}

void addEdge (Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in addEdge(); graph passed is NULL.\n");
        exit(1);
    }
    if (u <= 0 || u > getOrder(G)) {
        fprintf(stderr, "ERROR: in addEdge(); u argument is not in valid range.\n");
        exit(1);
    }
    if (v <= 0 || v > getOrder(G)) {
        fprintf(stderr, "ERROR: in addEdge(); v argument is not in valid range.\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
    return;
}

/*** Other Operations ***/
void printGraph(FILE * out, Graph G) {
    for (int i = 1; i < (G->order + 1); i++){
        fprintf(out, "%d:", i);
        printList(out, G->vertices[i]);
    }
    return;
}

/*
int main(void) {
    Graph G = newGraph(5);
    addEdge(G, 2, 4);
    addEdge(G, 1, 5);
    addEdge(G, 3, 5);
    addEdge(G, 2, 5);
    printGraph(stdout, G);
    BFS(G, 5);
    List L = newList();
    getPath(L, G, 4);
    printf("List Path:");
    printList(stdout, L);
    makeNull(G);
    printGraph(stdout, G); 
    //printf("Source Vertex: %d\n", getSource(G));
    //int c = 4;
   // printf("parent of %d: %d\n", c, getParent(G, c));
    //printf("Distance from %d to %d: %d\n", getSource(G), c, getDist(G, c));
    freeGraph(&G);
    freeList(&L);
    return 0;
}
*/
