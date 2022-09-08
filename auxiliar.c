#include "auxiliar.h"

// Função que testa a inicializa de malloc
void testeIniniciacao(bool teste, const char *descricao)
{
	if (teste)
		return;
	fprintf(stderr, "Erro: não foi possível inializar %s\n", descricao);
	exit(1);
}

// Função que lê agendamento S da entrada padrão,
// armazena em S e retorna o número de linhas do agendamento
int leAgendamentos(FILE *input, agendamento *S)
{
	int i = 0;
	*S = (agendamento)malloc(sizeof(transacao) * LIMITE);
	testeIniniciacao(*S, "AGENDAMENTO");
	while (fscanf(input, "%d %d %c %c\n", &(*S)[i].timestamp, &(*S)[i].id_transacao, &(*S)[i].operacao, &(*S)[i].item) == 4)
		i++;
	return i;
}

// Função que imprime IDs das transações no arquivo de saída padrão
void imprimeIDs(agendamento escalonamento, int num_linhas)
{
	int transacao = escalonamento[0].id_transacao;

	fprintf(stdout, "%d", transacao);

	for (int i = 1; i < num_linhas; i++)
	{
		if (escalonamento[i].id_transacao > transacao)
		{
			transacao = escalonamento[i].id_transacao;
			fprintf(stdout, ",%d", transacao);
		}
	}
	return;
}