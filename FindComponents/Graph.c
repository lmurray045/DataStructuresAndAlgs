/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa3
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

#define UNDEF -1
#define NIL 0

typedef struct GraphObj {
    List * vertices;
    //COLOR CODES: 0 == white, 1 == gray, 2 == black
    int * color;
    int * parent;
    int * discover;
    int * finish;
    int order;
    int size;
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
    G->discover = (int *)calloc((n+1), sizeof(int));
    G->finish = (int *)calloc((n+1), sizeof(int));
    for (int i = 1; i < (n+1); i++){
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    G->order = n;
    G->size = 0;
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
    free((*pG)->discover);
    free((*pG)->finish);
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

int getDiscover (Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getDiscover(): Graph passed is NULL.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "ERROR: in getDiscover(): vertice is out of range.\n");
        exit(1);
    }
    return G->discover[u];
}

int getFinish (Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in getFinish(): Graph passed is NULL.\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "ERROR: in getFinish(): vertice is out of range.\n");
        exit(1);
    }
    return G->finish[u];
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
    return G->parent[u];
}

/*** Manipulation Functions ***/

void visit (Graph G, int x, int * tp) {
    G->discover[x] = (++(*tp));
    G->color[x] = 1;
    moveFront(G->vertices[x]);
    for (int i = 0; i < length(G->vertices[x]); i++) {
        int elm = get(G->vertices[x]);
        if (G->color[elm] == 0) {
            G->parent[elm] = x;
            visit(G, elm, tp);
        }
        moveNext(G->vertices[x]);
    }
    G->color[x] = 2;
    G->finish[x] = (++(*tp));
    return;
}

void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "ERROR: in DFS(): Graph passed is NULL\n");
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "ERROR: in DFS(); List length is invalid.\n");
        exit(1);
    }
    for (int i = 0; i < getOrder(G) + 1; i++) {
        G->color[i] = 0;
        G->parent[i] = NIL;
    }
    int time = 0;
    int * tp = &time;
    moveFront(S);
    for (int i = 1; i < getOrder(G) + 1; i++) {
       int sN = get(S);
       if (G->color[sN] == 0) {
            visit(G, sN, tp);
       }
       moveNext(S);
    }
    clear(S);
    append(S, 1);
    for (int j = 2; j <= getOrder(G); j++) {
        moveFront(S);
        for (int i = 0; i < length(S)+1; i++) {
            if (index(S) == -1) {
                append(S, j);
                break;
            }
            if (G->finish[j] > G->finish[get(S)]) {
                insertBefore(S, j);
                break;
            }
            moveNext(S);
        }
    }   
    return;
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
    for (int i = 0; i < length(G->vertices[u]); i++){
    	if (get(G->vertices[u]) == ins) {
	    return;
	}
	moveNext(G->vertices[u]);
    }
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

Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "ERROR in copyGraph(): Graph input is NULL.\n");
        exit(1);
    }
    Graph nG = newGraph(getOrder(G));
    nG->size = getSize(G);
    for (int i = 1; i < (nG->order +1); i++){
        nG->vertices[i] = copyList(G->vertices[i]);
        nG->color[i] = G->color[i];
        nG->parent[i] = G->parent[i];
        nG->discover[i] = G->finish[i];
        nG->finish[i] = G->finish[i];
    }
    return nG;
}

Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "ERROR in transpose(): Graph input is NULL.\n");
        exit(1);
    }
    Graph nG = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        List x = G->vertices[i];
        moveFront(x);
        for (int j = 0; j < length(x); j++) {
            int n = get(x);
            addArc(nG, n, i);
            moveNext(x);
        }
    }
    return nG;
}


/*
int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");
   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
*/
