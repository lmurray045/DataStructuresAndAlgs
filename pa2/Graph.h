/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa2
* Graph.h
* Function definitions for Graph ADT Include File
************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define INF -1
#define NIL 0

/*** Structure Definitions ***/

typedef struct GraphObj GraphObj; 

typedef GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n); //creates a new graph with order n
void freeGraph(Graph* pG); //frees all graph memory

/*** Access functions ***/
//returns the order of Graph G;
int getOrder(Graph G);

//returns the size of Graph G
int getSize(Graph G);

//returns the last used soruce of BFS on Graph G
int getSource(Graph G);

//returns the parent of u in the most recent BFS tree of G
int getParent(Graph G, int u);

//returns the distance from u to the most recent source of BFS in G
int getDist(Graph G, int u);

//appends the shortest path from the source to u used in BFS on G
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

//deletes all edges on the graph
void makeNull(Graph G);

//adds a non-directed edge from u to v on graph G
void addEdge(Graph G, int u, int v);

//adds a directed edge from u to v on graph G
void addArc(Graph G, int u, int v);

//performs BFS on G
void BFS(Graph G, int s);

/*** Other operations ***/

//prints the graph G in adjanceny list form to the outfile 
void printGraph(FILE* out, Graph G);




#endif
