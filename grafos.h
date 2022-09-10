#ifndef __GRAFOS__
#define __GRAFOS__

// Estrutura para armazenar os números de pré e pós-ordem de um vértice v,
// obtidos por meio de uma busca em profundidade (DFS) em um grafo 
typedef struct
{
	int pre;				// número de pré-ordem de v
	int pos;				// número de pós-ordem de v
} estado;

// Estrutura para armazenar a representação de um grafo,
// cujos vértices são as transações de um escalonamento
typedef struct
{
	int n;					// número de vértices
	int *matriz_adj;			// matriz de adjacência para representar os arcos do grafo
	estado *estado;				// vetor de estados dos vértices
	int *ordem_topologica;			// vetor de ordenação topológica, que será formada caso haja ciclo no grafo
} grafo;

// FUNÇÕES
grafo *criaGrafoTransacoes(agendamento S, int num_linhas, int num_transacoes);
void buscaProfundidadeVertice(grafo *G, int v);
int *buscaCiclosTransacoes(grafo *G);

#endif
