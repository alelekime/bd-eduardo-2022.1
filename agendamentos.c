#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "auxiliar.h"

// Função que recebe um agendamento e seu número
// de linhas e retorna a quantidade de transações
int contaTransacoes(agendamento S, int num_linhas)
{
	int num_transacoes = 0;

	for (int i = 0; i < num_linhas; i++)
		if (S[i].id_transacao > num_transacoes)
			num_transacoes = S[i].id_transacao;

	return num_transacoes;
}

// Função que calcula o número de transações que fazem parte
// de ciclos em um agendamento S
int contaTransacoesEmCiclos(int *ciclos, int num_transacoes)
{
	int num_ciclos = 0;

	for (int i = 0; i < num_transacoes; i++)
		if (ciclos[i])												// se uma transação faz parte de um ciclo
			num_ciclos++;											// incrementa o contador
	return num_ciclos;
}

// Função que cria vetor com as transações que possuem conflito
// (que fazem parte de um ciclo)
int *transacoesConflitantes(int *ciclos, int num_transacoes, int num_ciclos)
{
	int *transacoes = (int *) malloc(sizeof (int) * num_ciclos);

	if (!transacoes)
	{
		fprintf(stderr, "Erro: não foi possível alocar vetor de transações conflitantes.\n");
		exit(-4);
	}
	int j = 0;
	for (int i = 0; i < num_transacoes; i++)
		if (ciclos[i])
			transacoes[j++] = i;
	return transacoes;
}

// Função que cria vetor com as transações que são serializáveis 
// por conflito (que NÃO fazem parte de um ciclo)
int *transacoesSerializaveis(int *ciclos, int num_transacoes, int num_ciclos)
{
	int *transacoes = (int *) malloc(sizeof (int) * num_ciclos);
	
	if (!transacoes)
	{
		fprintf(stderr, "Erro: não foi possível alocar vetor de transações serializáveis.\n");
		exit(-5);
	}
	int j = 0;
	for (int i = 0; i < num_transacoes; i++)
		if (!ciclos[i])
			transacoes[j++] = i;
	return transacoes;
}