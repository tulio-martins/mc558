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
    int pellets[4];

    int n_ghosts;
    int ghosts[4];

    scanf("%d %d", &n_nodes, &m_edges);

    /*inicializando o grafo*/
    g = initGraph(n_nodes);

    /*adicionando as arestas*/
    for(int i = 0; i < m_edges; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      addEdgeToGraph(g, u, v);
    }

    scanf("%d", &source);

    scanf("%d", &n_pellets);
    for(int i = 0; i < 4; i++)
      pellets[i] = 101;
    for(int i = 0; i < n_pellets; i++)
      scanf("%d", &pellet[i]);

    scanf("%d", &n_ghosts);
    for(int i = 0; i < 4; i++)
      ghosts[i] = 101;
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
  int possible_pellets[4];
  int poss_index;
  int pi[100];
  int u;
  int pp_index = 0;


  for(int i = 0; i < 100; i++)
    pi[i] = 101;

  enqueue(q, source);
  g->AdjacencyList[source].colour = GREY;
  while(q) {
    u = dequeue(&q);
    for(pAdjListNode n = g->AdjacencyList[u].head; n->next != NULL; n = n->next) {
      if(notGhost(n->v, ghosts) && g->AdjacencyList[n->v].colour != BLACK) {
        if(isPellet(n->v) && g->AdjacencyList[n->v].colour == WHITE) {
          stop_queuing = TRUE;
          possible_pellets[pp_index++] = n->v;
        }
        if(pi[n->v] > u)
          pi[n->v] = u;
        if(g->AdjacencyList[n->v].colour == WHITE) {
          g->AdjacencyList[n->v].colour = GREY;
          if (stop_queuing == FALSE)
            enqueue(q, n->v);
        }
      }
    }
    g->AdjacencyList[u->v].colour = BLACK;
  }

  rs->pellet_node = possible_pellets[0];

  for(int i = 1; i < 4; i++) {
    if(possible_pellets[i] < rs->pellet_node)
      rs->pellet_node = possible_pellets[i];
  }
  rs->first_step = firstStepOfPacman(pi, rs->pellet_node, source);

  return rs;
}

void enqueue(Queue q, int v) {
  Queue i;
  Queue newQ = malloc(sizeof(queue));

  newQ->v = v;

  while(i->next !+ NULL) {
    i = i->next;
  }

  i->next = newQ;
  newQ->next = NULL;
}

int dequeue(Queue *q) {
  int ret = q->v;
  Queue old = (*q);

  (*q) = (*q)->next;
  free(old);

  return ret;
}

int notGhost(int x, int ghosts[]) {

  for(int i = 0; i < 4; i++) {
    if(x == ghosts[i]) {
      return 0;
    }
  }
  return 1;
}

int isPellet(int x, int pellets[]) {

  for(int i = 0; i < 4; i++) {
    if(x == pellets[i]) {
      return 1;
    }
  }
  return 0;
}

firstStepOfPacman(int pi[], int pellet, int source) {
  int x = pi[pellet];

  if(x == source)
    return pellet;

  while(pi[x] != source)
    x = pi[x];

  return x;
}
