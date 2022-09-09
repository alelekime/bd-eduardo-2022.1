#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "grafos.h"

// VARIÁVEIS GLOBAIS
int instante;
int ordem;

// Função que cria grafo de transações de um agendamento
// de acordo com algoritmo de serialização por conflito
grafo *criaGrafoTransacoes(agendamento S, int num_linhas, int num_transacoes)
{
	grafo *G = (grafo *) malloc(sizeof (grafo));
	if (!G)
	{
		fprintf(stderr, "Erro: não foi possível alocar grafo.\n");
		exit(-2);
	}

	G->n = num_transacoes;										// inicializa número de vértices com número de transações
	G->matriz_adj = (int *) malloc(sizeof (int) * G->n * G->n);
	if (!G->matriz_adj)
	{
		fprintf(stderr, "Erro: não foi possível alocar matriz de adjacência.\n");
		exit(-2);
	}
	memset(G->matriz_adj, 0, sizeof (int) * G->n * G->n);		// inicializa matriz de adjacência com zeros


	// laço que percorre o agendamento S para determinar arcos do grafo
	for (int i = 0; i < num_linhas; i++)
		for (int j = i + 1; j < num_linhas; j++)		
			// se duas transações diferentes de um agendamento S manipulam um mesmo item
			if ((S[i].id_transacao != S[j].id_transacao) && (S[i].item == S[j].item))
			{
				// se há R(x) em Tj depois de W(x) em Ti
				if ((S[i].operacao == 'W') && (S[j].operacao == 'R'))
					// insere um arco Ti -> Tj na matriz
					G->matriz_adj[(S[i].id_transacao - 1) * G->n + (S[j].id_transacao - 1)]++;
				// se há W(x) em Tj depois de R(x) em Ti
				if ((S[i].operacao == 'R') && (S[j].operacao == 'W'))
					// insere um arco Ti -> Tj na matriz
					G->matriz_adj[(S[i].id_transacao - 1) * G->n + (S[j].id_transacao - 1)]++;					
				// se há W(x) em Tj depois de W(x) em Ti
				if ((S[i].operacao == 'W') && (S[j].operacao == 'W'))
					// insere um arco Ti -> Tj na matriz
					G->matriz_adj[(S[i].id_transacao - 1) * G->n + (S[j].id_transacao - 1)]++;	
			}	
	return G;
}

// Função recursiva de busca em profundidade em um grafo a partir de um vértice,
// que marca os valores de pré e de pós-ordem da vizinhança do vértice
// e gera a ordem topológica para os casos em que há ciclo
void buscaProfundidadeVertice(grafo *G, int v)
{
	G->estado[v].pre = ordem++;										// calcula valor de pré-ordem do vértice v
	// laço que percorre matriz de adjacência em busca de vizinhos do vértice
	for (int i = 0; i < G->n; i++)		
		if (G->matriz_adj[(v * G->n) + i])							// caso encontre um vértice da vizinhança de v
			if (G->estado[i].pre == -1)								// que ainda não tenha sido processado		
				buscaProfundidadeVertice(G, i);						// faz uma chamada recursiva da busca
	
	if (instante < G->n)
		G->ordem_topologica[instante++] = v;						// adiciona o valor do vértice à ordem topológica
	G->estado[v].pos = ordem++;										// calcula valor de pós-ordem do vértice v
	return;
}

// Função que descobre se uma transação de um agendamento Sfaz parte de 
// um ciclo em um grafo, por meio de uma busca em profundidade (DFS).
// Retorna um vetor de ciclos com valor igual 1 para transações que 
// fazem parte de um ciclo e 0 para aquelas que não fazem
int *buscaCiclosTransacoes(grafo *G)
{
	instante = 0;
	ordem = 0;

	G->estado = (estado *) malloc(sizeof (estado) * G->n);
	if (!G->estado)
	{
		fprintf(stderr, "Erro: não foi possível alocar vetor de estados do grafo.\n");
		exit(-3);
	}

	G->ordem_topologica = (int *) malloc(sizeof (int) * G->n);
	if (!G->ordem_topologica)
	{
		fprintf(stderr, "Erro: não foi possível alocar vetor de ordem topológica do grafo.\n");
		exit(-3);
	}

	int *ciclos = (int *) malloc(sizeof (int) * G->n);
	if (!ciclos)
	{
		fprintf(stderr, "Erro: não foi possível alocar vetor de ciclos do grafo.\n");
		exit(-3);
	}
	memset(ciclos, 0, sizeof (int) * G->n);							// inicializa vetor de ciclos com zeros

	for (int i = 0; i < G->n; i++)
		G->estado[i].pre = -1;										// inicializa a pré-ordem das transações como -1

	// laço que percorre o grafo para calcular pré e pós-ordem das transações
	for (int v = 0; v < G->n; v++)
		if (G->estado[v].pre == -1)									// caso o vértice v ainda não tenhsa sido processado
			buscaProfundidadeVertice(G, v);							// chama função de DFS para processá-lo

	// laço que percorre o grafo de transações para sinalizar as que fazem parte de um ciclo
	for (int v = 0; v < G->n; v++)
		for (int i = 0; i < G->n; i++)								// percorre a matriz de adjacência da transação v
			if (G->matriz_adj[(v * G->n) + i])						// caso encontre um vértice da vizinhança de v
				if (G->estado[v].pos < G->estado[i].pos)			// que esteja ligado à transação v por uma aresta de retorno
				{
					ciclos[v] = 1;									// sinaliza que a transação v faz parte de um ciclo
					ciclos[i] = 1;									// do qual a transação i também faz parte 
				}
	return ciclos;
}
