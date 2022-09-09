#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "auxiliar.h"

// int findChar(char *str, int n, char c)
// {
// 	for (int i = 0; i < n; i++)
// 		if (str[i] == c)
// 			return i;
// 	return -1;
// } // FINALIZADA

// int *encontraOperacoes(agendamento S, int *numeroOperacoes, int num_transacoes, char *operacoes, int *indiceOperacoes)
// {
// 	int *vcount = (int *)malloc(sizeof(int) * n);
// 	memset(vcount, 0, sizeof(int) * n);

// 	int k = 1;

// 	for (int i = 0; i < n; i++)
// 	{
// 		if (T[i].op != 'C')
// 		{
// 			int achou = findChar(atb, n, T[i].atb);
// 			if (achou >= 0)
// 			{
// 				vcount[achou]++;
// 			}
// 			else
// 			{
// 				atb[k] = T[i].atb;
// 				vcount[k++]++;
// 			}
// 		}
// 	}

// 	vcount[0] = k - 1;

// 	vcount = (int *)realloc(vcount, sizeof(int) * (k));
// 	return vcount;
// } // FINALIZADA

// int equivalenciaPorVisao(agendamento *S, int num_transacoes)
// {
// 	char *operacoes = malloc(sizeof(char) * num_transacoes);
// 	int *indiceOperacoes = malloc(sizeof(int) * num_transacoes);
// 	memset(indiceOperacoes, 0, sizeof(int) * num_transacoes);
// 	int * numeroOperacoes;
// 	encontraOperacoes(S, numeroOperacoes, num_transacoes, operacoes, indiceOperacoes);

// 	int finalIdsWrite[indiceOperacoes[0]];
// 	int finalTimeInWrite[indiceOperacoes[0]];
// 	int fid = 0;
// 	int fti = 0;

// 	for (int atb = 0; atb < indiceOperacoes[0]; atb++) // para cada diferente atributo encontrado em todas as transações
// 	{
// 		int findFinal = 0;
// 		for (int i = indiceOperacoes[atb + 1] - 1; i >= 0 && !findFinal; i--)
// 			if (T[atb][i].op == 'W') // verificar se existe alguma operação de escrita sobre determinado atributo
// 			{
// 				finalIdsWrite[fid++] = T[atb][i].id;		// guardar o identificador da transação que tenha essa operação de escrita
// 				finalTimeInWrite[fti++] = T[atb][i].timeIn; // guardar o tempo de chegada da transação que tenha essa operação de escrita
// 				findFinal = 1;								// quebra a repetição
// 			}
// 	}

// 	int finalW = 1;

// 	for (int atb = 0; atb < indiceOperacoes[0]; atb++) // iteração sobre a lista de atributos encontrados
// 		for (int t = indiceOperacoes[atb + 1] - 1; t >= 0 && finalW; t--)
// 		{ // encontrar duas transações (diferentes IDs), que operem uma escrita sobre um atributo e que não seja a última escrita de determinada transação
// 			if ((T[atb][t].timeIn > finalTimeInWrite[atb]) && (T[atb][t].op == 'W') && (T[atb][t].id != finalIdsWrite[atb]))
// 				finalW = 0;
// 		}
// 	return finalW;
// } // FINALIZADA

// Função que recebe um agendamento e seu número
// de linhas e retorna a posicao da escrita ou se nao teve escrita
int encontraEscrita(agendamento S, int num_transacoes)
{
	int i;
	for (i = 0; i < num_transacoes; i++)
	{
		if (S[i].operacao == 'W')
		{
			return i;
		}
	}
	return -1;
}

// Função que recebe um agendamento e um indice verifica se houve leitura antes da escrita(mesmo tx e attr)
int verificaEscrita(agendamento S, int idEscrita)
{
	int j;
	for (j = 0; j < idEscrita; j++)
		if ((S[j].operacao == 'R') && (S[j].item == S[idEscrita].item) && (S[j].id_transacao == S[idEscrita].id_transacao))
			return 1;
	return 0;
}

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

// Função que recebe um escalonamento e seu número
// de linhas e retorna a quantidade de transações
int contaTransacoesEscalonamento(agendamento S, int num_linhas)
{
	int num_transacoes = 0;

	for (int i = 0; i < num_linhas; i++)
		if (S[i].operacao == 'C')
			num_transacoes++;

	return num_transacoes;
}

// Função que calcula o número de transações que fazem parte
// de ciclos em um agendamento S
int contaTransacoesEmCiclos(int *ciclos, int num_transacoes)
{
	int num_ciclos = 0;

	for (int i = 0; i < num_transacoes; i++)
		if (ciclos[i])	  // se uma transação faz parte de um ciclo
			num_ciclos++; // incrementa o contador
	return num_ciclos;
}

// Função que cria vetor com as transações que possuem conflito
// (que fazem parte de um ciclo)
int *transacoesConflitantes(int *ciclos, int num_transacoes, int num_ciclos)
{
	int *transacoes = (int *)malloc(sizeof(int) * num_ciclos);

	if (!transacoes)
	{
		fprintf(stderr, "Erro: não foi possível alocar vetor de transações conflitantes.\n");
		exit(-5);
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
	int *transacoes = (int *)malloc(sizeof(int) * num_ciclos);

	if (!transacoes)
	{
		fprintf(stderr, "Erro: não foi possível alocar vetor de transações serializáveis.\n");
		exit(-6);
	}
	int j = 0;
	for (int i = 0; i < num_transacoes; i++)
		if (!ciclos[i])
			transacoes[j++] = i;
	return transacoes;
}