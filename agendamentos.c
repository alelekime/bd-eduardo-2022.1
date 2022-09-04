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