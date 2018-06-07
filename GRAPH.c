#include "GRAPH.h"
#include <stdio.h>
#include <stdlib.h>
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
Graph initGraph(int n){
    int i;
    Graph G = (Graph)malloc(sizeof(graph));
    G->n = n;
    G->AdjacencyList = (pAdjList)malloc(n * sizeof(AdjList));
    for (i = 0; i < n; i++) {
        G->AdjacencyList[i].head = NULL;
        G->AdjacencyList[i].colour = WHITE;
    }

    return G;
}
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
pAdjListNode createNode(int v) {
    pAdjListNode newNode = (pAdjListNode)malloc(sizeof(AdjListNode));
    newNode->v = v;
    newNode->next = NULL;
    return newNode;
}
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
void addEdgeToGraph(Graph G, int u, int v){
    pAdjListNode newNode_u = createNode(u);
    pAdjListNode newNode_v = createNode(v);

    newNode_v->next = G->AdjacencyList[u].head;
    G->AdjacencyList[u].head = newNode_v;
    newNode_u->next = G->AdjacencyList[v].head;
    G->AdjacencyList[v].head = newNode_u;
    return;
}

