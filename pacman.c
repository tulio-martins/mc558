#include "GRAPH.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _ResultSet {
  int first_step; // O no que eh o primeiro caminho da fonte
  int pellet_node;// O no que eh o power pellet
} ResultSet;

typedef struct _Queue {
  int v;
  struct _Queue *next;
} queue, *Queue;

int main() {
    /*Definindo variaveis*/
    ResultSet rs;
    int n_nodes;
    int m_edges;
    Graph g;
    Queue q = NULL;

    int source;
    int n_pellets;
    int *pellets;

    scanf("%d %d", &n_nodes, &m_edges);

    /*inicializando o grafo*/
    g = initGraph(n_nodes);

    /*adicionando as arestas*/
    for(int i = 0; i < m_nodes; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      addEdgeToGraph(g, u, v);
    }

    scanf("%d", &source);

    scanf("%d", &n_pellets);
    pellets = malloc(n_pellets*sizeof(int));
    for(int i = 0; i < n_pellets; i++)
      scanf("%d", &pellet[i]);

    scanf("%d", &n_ghosts);
    ghosts = malloc(n_ghosts*sizeof(int));
    for(int i = 0; i < n_ghosts; i++)
      scanf("%d", &ghosts[i]);

    /*BFSearch*/
    rs = BFSearch(g, source, pellets, ghosts, q);

    printf("First Pellet: %d\n", rs.pellet_node);
    printf("First Step: %d\n", rs.first_step);

    return 0;
}

ResultSet BFSearch(Graph g, int source, int pellets[], int ghosts[], Queue q) {
  ResultSet rs;
  int stop_queuing = FALSE;
  int possible_pellets = malloc(n*sizeof(pellets)); /*(!!!!!!!)*/
  //int pi = source;


  for(pAdjListNode n = g->AdjacencyList[source].head; n != NULL; n = n->next) {
    if(notGhost(n->v)) {
      if(isPellet(n->v)) {
        stop_queueing = TRUE;
      } else {
        enqueue(n->v);
      }
    }
  }

  if(stop_queing) {

  }



  return rs;
}
