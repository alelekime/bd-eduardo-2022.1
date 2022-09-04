#ifndef __GRAFOS__
#define __GRAFOS__

// Estrura para armazenar os números de pré e pós-ordem de um vértice v,
// obtidos por meio de uma busca em profundidade (DFS) em um grafo 
typedef struct
{
	int pre;				// número de pré-ordem de v
	int pos;				// número de pós-ordem de v
} estado;

// Estrutura para armazenar a representação de um grafo,
// cujos vértices são as transações do agendamento
typedef struct
{
	int n;					// número de vértices
	int *matriz_adj;		// matriz de adjacência para representar os arcos do grafo
	estado *estado;			// vetor de estados dos vértices
	int *ordem_topologica;	// ordenação topológica que será formada caso haja ciclo no grafo
} grafo;

// FUNÇÕES
grafo *criaGrafoTransacoes(agendamento S, int num_linhas, int num_transacoes);

#endif