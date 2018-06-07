/* GRAPH.h */
/* Header file com estruturas, definições e pragmas. */
/* Autor: Celso A. W. Santos */
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*   -- // -- // -- // --   *
 * Definições de estruturas *
 *   -- // -- // -- // --   */
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* Cores de vértices para BFS */
typedef enum _NodeColour {BLACK, WHITE, GRAY} NodeColour;
/* Estrutura de nó (e ponteiro) para Lista de Adjacências */
typedef struct _AdjListNode {
    int v;
    struct _AdjListNode * next;
} AdjListNode, *pAdjListNode;
/* Estrutura para armazenar informações de vértices  */
typedef struct _AdjList {
    NodeColour colour;
    AdjListNode * head;
} AdjList, *pAdjList;
/* Estrutura do Grafo */
typedef struct _Graph {
    int n;                      /* Ordem de G */
    AdjList * AdjacencyList;    /* Vetor de listas de adjacências */
} graph;
typedef graph * Graph;
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*   -- // -- // -- // --    *
 * Funções básicas de Grafos *
 *   -- // -- // -- // --    */
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* Inicialização de um grafo G */
Graph initGraph(int V);
/* Criar nó de lista de adjacência */
pAdjListNode createNode(int v);
/* Adicionando aresta no grafo */
void addEdgeToGraph(Graph G, int u, int v);
/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
