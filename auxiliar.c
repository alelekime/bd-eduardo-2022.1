#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "agendamentos.h"
#include "auxiliar.h"
#include "grafos.h"

void testaInicializacao(bool teste, char *descricao)
{
	if (teste)
		return;
	printf("Erro: não foi possível inicializar %s\n", descricao);
	exit(1);
}

// Função que lê agendamento S da entrada padrão,
// armazena em S e retorna o número de linhas do agendamento
int leAgendamentos(FILE *input, agendamento *S)
{
	int i = 0;
	*S = malloc(sizeof(agendamento) * LIMITE);
	testaInicializacao(S, "AGENDAMENTO");

	while (fscanf(input, "%d %d %c %c\n", &(*S)[i].timestamp, &(*S)[i].id_transacao, &(*S)[i].operacao, &(*S)[i].item) == 4)
		i++;
	return i;
}
// funcao de ordenaçao
int cmpfunc(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

// Função que imprime IDs das transações no arquivo de saída padrão
void imprimeIDs(agendamento escalonamento, int num_linhas, int num_transacoes)
{
	int i, j, k = 0;
	int *transasoesDistintas = malloc(sizeof(int) * num_linhas);
	memset(transasoesDistintas, 0, sizeof(int) * num_linhas); // limpa o vetor
	transasoesDistintas[0] = escalonamento[0].id_transacao;
	fprintf(stdout, "%d", transasoesDistintas[0]);
	int achou = 1;
	for (i = 1; i < num_linhas; i++)
	{
		k = 0;
		for (j = 0; j < num_transacoes; j++)
		{
			if (escalonamento[i].id_transacao == transasoesDistintas[j])
			{
				k = 1;
				break;
			}
		}
		if (!k)
		{
			transasoesDistintas[achou] = escalonamento[i].id_transacao;
			achou++;
		}
	}
	qsort(transasoesDistintas, achou, sizeof(int), cmpfunc);

	for (i = 1; i < achou; i++)
		fprintf(stdout, ",%d", transasoesDistintas[i]);
	return;
}