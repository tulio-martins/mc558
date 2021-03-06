/*Tulio Brandao Soares Martins
  Codigo Academico
  materia - mc558
  ra177761*/

#include "GRAPH.h"
#include <stdio.h>
#include <stdlib.h>



typedef struct _ResultSet {
  int first_step;
  int pellet_node;
} ResultSet;

typedef struct _Queue {
  int v;
  struct _Queue *next;
} queue, *Queue;

/*Realiza uma BFSearch e devolve o primeiro passo do pacman e onde esta o pellet*/
ResultSet BFSearch(Graph g, int source, int pellets[], int ghosts[], Queue q);
/*Enfilera um inteiro v*/
void enqueue(Queue *q, int v);
/*Desenfilera o primeiro inteiro da fila q e o retorna*/
int dequeue(Queue *q);
/*Devolve se a casa x possui fantasma - 1 se sim - 0 se nao*/
int notGhost(int x, int ghosts[]);
/*Devolve se a casa x possui um pellet - 1 se sim - 0 se nao*/
int isPellet(int x, int pellets[]);
/*Encontra o primeiro passo que um pacman deve realizar se um pellet esta em "pellet"*/
int firstStepOfPacman(int pi[], int pellet, int source);
/*Decide entre o candidato e o atual qual dos pellets deve ser escolhido*/
int comesFirst(int candidate, int actual, int pellets[]);

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

    int i;

    scanf("%d %d", &n_nodes, &m_edges);

    /*inicializando o grafo*/
    g = initGraph(n_nodes);

    /*adicionando as arestas*/
    for(i = 0; i < m_edges; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      addEdgeToGraph(g, u, v);
    }

    scanf("%d", &source);

    scanf("%d", &n_pellets);
    for(i = 0; i < 4; i++)
      pellets[i] = 101;
    for(i = 0; i < n_pellets; i++)
      scanf("%d", &pellets[i]);

    scanf("%d", &n_ghosts);
    for(i = 0; i < 4; i++)
      ghosts[i] = 101;
    for(i = 0; i < n_ghosts; i++)
      scanf("%d", &ghosts[i]);


    /*BFSearch*/
    rs = BFSearch(g, source, pellets, ghosts, q);

    printf("First Pellet:\t%3d\nFirst Step:\t%3d\n", rs.pellet_node, rs.first_step);

    return 0;
}

/*Realiza uma BFSearch e devolve o primeiro passo do pacman e onde esta o pellet*/
ResultSet BFSearch(Graph g, int source, int pellets[], int ghosts[], Queue q) {
  ResultSet rs;
  int stop_queuing = 0;
  int possible_pellets[4];
  int pi[100];
  int u;
  int pp_index = 0;
  int i;
  pAdjListNode n;


  for(i = 0; i < 100; i++)
    pi[i] = 101;
  for(i = 0; i < 4; i++)
    possible_pellets[i] = 101;

  enqueue(&q, source);
  g->AdjacencyList[source].colour = GRAY;
  /*enquanto existir alguma casa a ser visitada*/
  while(q) {
    u = dequeue(&q);
    /*passeando por todos os vizinhos de u(que havia sido enfileirado)*/
    for(n = g->AdjacencyList[u].head; n != NULL; n = n->next) {
      /*ignora casa que tem fantasma ou ja foi visitada*/
      if(notGhost(n->v, ghosts) && g->AdjacencyList[n->v].colour != BLACK) {
        /*guarda um novo pellet como candidato*/
        if(isPellet(n->v, pellets) && g->AdjacencyList[n->v].colour == WHITE) {
          stop_queuing = 1;
          possible_pellets[pp_index++] = n->v;
        }
        /*decide o menor pai possivel para n*/
        if(pi[n->v] > u) {
          pi[n->v] = u;
        }
        /*pinta o vertice branco como visitado*/
        if(g->AdjacencyList[n->v].colour == WHITE) {
          g->AdjacencyList[n->v].colour = GRAY;
          /*caso nao tenham encontrado o pellet ainda, continua a busca*/
          if (stop_queuing == 0)
            enqueue(&q, n->v);
        }
      }
    }
    /*declara u como visitado*/
    g->AdjacencyList[u].colour = BLACK;
  }

  /*inicializa o pellet a ser escolhido*/
  rs.pellet_node = possible_pellets[0];

  /*decide qual sera o pellet que o pacman escolhera*/
  for(i = 1; i < 4; i++) {
    if(comesFirst(possible_pellets[i], rs.pellet_node, pellets)) {
      rs.pellet_node = possible_pellets[i];
    }
  }
  /*ncontrao o primeiro passo de um pacman dado um pellet*/
  rs.first_step = firstStepOfPacman(pi, rs.pellet_node, source);

  return rs;
}

/*Enfilera um inteiro v*/
void enqueue(Queue *q, int v) {
  Queue newQ = malloc(sizeof(queue));
  Queue i = (*q);

  newQ->v = v;
  newQ->next = NULL;

  if((*q) == NULL) {
    (*q) = newQ;
  } else {
    while(i->next != NULL) {
      i = i->next;
    }
    i->next = newQ;
  }
}

/*Desenfilera o primeiro inteiro da fila q e o retorna*/
int dequeue(Queue *q) {
  int ret = (*q)->v;
  Queue old = (*q);

  (*q) = (*q)->next;
  free(old);

  return ret;
}

/*Devolve se a casa x possui fantasma - 1 se sim - 0 se nao*/
int notGhost(int x, int ghosts[]) {
  int i;

  for(i = 0; i < 4; i++) {
    if(x == ghosts[i]) {
      return 0;
    }
  }
  return 1;
}

/*Devolve se a casa x possui um pellet - 1 se sim - 0 se nao*/
int isPellet(int x, int pellets[]) {
  int i;

  for(i = 0; i < 4; i++) {
    if(x == pellets[i]) {
      return 1;
    }
  }
  return 0;
}

/*Encontra o primeiro passo que um pacman deve realizar se um pellet esta em "pellet"*/
int firstStepOfPacman(int pi[], int pellet, int source) {
  int x = pi[pellet];

  /*de o primeiro passo for ir direto ao pellet*/
  if(x == source)
    return pellet;

  /*anda pelos pais do pellet ate que o pai de x seja o source, o que faz de x */
  /*o primeiro passo ate chegar no pellet*/
  while(pi[x] != source)
    x = pi[x];

  return x;
}

/*Decide entre o candidato e o atual qual dos pellets deve ser escolhido*/
int comesFirst(int candidate, int actual, int pellets[]) {
  int i;
  for(i = 0; i < 4; i++) {
    if(pellets[i] == actual)
      return 0;
    else
      if(pellets[i] == candidate)
        return 1;
  }
  return 0;
}
