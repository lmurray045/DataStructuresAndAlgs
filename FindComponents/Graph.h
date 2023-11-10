/************************************************
* Liam Murray, lijamurr
* CSE101 Spring 2023, Pa3
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

#define UNDEF -1
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

//returns the finish time of U in the DFS tree of G
int getFinish (Graph G, int u);

//returns the discover time of U in the DFS tree of G
int getDiscover (Graph G, int u);

/*** Manipulation procedures ***/

//deletes all edges on the graph
void makeNull(Graph G);

//adds a non-directed edge from u to v on graph G
void addEdge(Graph G, int u, int v);

//adds a directed edge from u to v on graph G
void addArc(Graph G, int u, int v);

//performs DFS on G, using the order in list L
void DFS(Graph G, List S);

/*** Other operations ***/

//prints the graph G in adjanceny list form to the outfile 
void printGraph(FILE* out, Graph G);

//returns a copy of Graph G
Graph copyGraph(Graph G);

//returns the transposed version of Graph G;
Graph transpose(Graph G);



#endif
