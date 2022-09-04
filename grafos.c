#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "grafos.h"

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
	{
		for (int j = i + 1; j < num_linhas; j++)
		{
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
		}
	}
	return G;
}