#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "auxiliar.h"
#include "grafos.h"


// Função que lê agendamento S da entrada padrão,
// armazena em S e retorna o número de linhas do agendamento
int leAgendamentos(FILE *input, agendamento *S) 
{
	int i = 0, limite = 40;
	*S = (agendamento) malloc(sizeof (transacao) * limite);
	if (!S)
	{
		fprintf(stderr, "Erro: não foi possível alocar agendamento.\n");
		exit(-1);
	}

	while (fscanf(input, "%d %d %c %c\n", &(*S)[i].timestamp, &(*S)[i].id_transacao, &(*S)[i].operacao, &(*S)[i].item) == 4)
	{
		i++;
		if (i >= limite)
		{
			limite += 5;
			*S = (agendamento) realloc(*S, sizeof (transacao) * limite);
			if (!S)
			{
				fprintf(stderr, "Erro: não foi possível realocar agendamento.\n");
				exit(-1);
			}
		}
	}
	*S = (agendamento) realloc(*S, sizeof (transacao) * i);
	return i;
}

// Função que imprime IDs das transações no arquivo de saída padrão
//void imprimeIDs(int *transacoes, int n)
//{
//	for (int i = 0; i < n; i++)
//		fprintf(stdout, "%d%c", transacoes[i] + 1, i + 1 >= n ? ' ' : ',');
//	return;
//} 