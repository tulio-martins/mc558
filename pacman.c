#include "GRAPH.h"

typedef struct _ResultSet {
  int first_step; // O no que eh o primeiro caminho da fonte
  int pellet_node;// O no que eh o power pellet
} ResultSet;

int main() {
    /*Definindo variaveis*/
    ResultSet rs;
    int n_nodes;
    int m_edges;
    Graph g;

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

    /*BFS*/
    rs = BFSearch(g, source, pellets, ghosts);

    printf("First Pellet: %d\n", rs.pellet_node);
    printf("First Step: %d\n", rs.first_step);

    return 0;
}

ResultSet BFSearch(Graph g, int source, int pellets[], int ghosts[]) {
  ResultSet rs;

  return rs;
}
