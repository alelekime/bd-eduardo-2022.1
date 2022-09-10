/*  T2 CI-218 - Sistemas de Banco de Dados - UFPR
 *   Orientação: prof. Dr. Eduardo Almeida
 *   Autoras:
 *           Alessandra Souza da Silva   GRR20182558
 *           Marisa Sel Franco           GRR20186556
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "agendamentos.h"
#include "auxiliar.h"
#include "grafos.h"

int main()
{
    int id, num_linhas = 0, num_transacoes = 0, num_escalonamentos = 0, num_linhas_escalonamento = 0, inicio = 0;
    agendamento S = NULL;

    num_linhas = leAgendamentos(stdin, &S);
    num_transacoes = contaTransacoes(S, num_linhas);

    int posicao_limite[num_transacoes];
    for (int i = 0; i < num_transacoes; i++)
        posicao_limite[i] = -1;

    // laço que percorre o agendamento S com as transações da entrada para identificar todos os escalonamentos
    for (int i = 0; i < num_linhas; i++)
    {
        if ((S[i].operacao == 'C') && ((i + 1 == num_linhas) || (S[i + 1].operacao != 'C')))
        {
            posicao_limite[num_escalonamentos] = i;
            num_escalonamentos++;
        }
    }

    // para cada escalonamento presente no agendamento S de entrada
    for (int i = 0; i < num_escalonamentos; i++)
    {
        id = i + 1; // calcula id do escalonamento
        if (i == 0) // calcula num. de linhas para o primeiro escalonamento
            num_linhas_escalonamento = posicao_limite[i] + 1;
        else // calcula início e num. de linhas para os demais escalonamentos
        {
            inicio = posicao_limite[i - 1] + 1;
            num_linhas_escalonamento = posicao_limite[i] + 1 - inicio;
        }
        // cria um escalonamento de fato a partir do agendamento S
        agendamento escalonamento = (agendamento)malloc(sizeof(transacao) * num_linhas);
        testaInicializacao(escalonamento, "ESCALONAMENTO");
        for (int i = inicio, j = 0; i < (num_linhas + inicio); i++, j++)
        {
            escalonamento[j].timestamp = S[i].timestamp;
            escalonamento[j].id_transacao = S[i].id_transacao;
            escalonamento[j].operacao = S[i].operacao;
            escalonamento[j].item = S[i].item;
        }
        num_transacoes = contaTransacoesEscalonamento(escalonamento, num_linhas_escalonamento);
        grafo *grafo_transacoes = criaGrafoTransacoes(escalonamento, num_linhas_escalonamento, num_transacoes);
        int *ciclos = buscaCiclosTransacoes(grafo_transacoes);
        int num_transacoes_ciclos = contaTransacoesEmCiclos(ciclos, num_transacoes);

        // se o grafo NÃO tem CICLOS
        if (num_transacoes_ciclos == 0)
        {
            fprintf(stdout, "%d ", id);
            imprimeIDs(escalonamento, num_linhas_escalonamento);
            fprintf(stdout, " .SS SV\n"); // o agendamento é serializável por conflito e por visão
        }
        // se o grafo TEM CICLOS
        else
        {
            // análise da serialidade por conflito
            fprintf(stdout, "%d ", id);
            imprimeIDs(escalonamento, num_linhas_escalonamento);
            fprintf(stdout, " NS "); // o agendamento NÃO é serializável por conflito
            int idEscrita = encontraEscrita(S, num_transacoes);
            int verificaEscritaTrasacao = verificaEscrita(S, idEscrita);

            if (!verificaEscritaTrasacao)
                if (equivalenciaPorVisao(&S, num_transacoes))
                    fprintf(stdout, "SV\n"); // SV se o retorno da função for 1
                else
                    fprintf(stdout, "NV\n"); // não é equivalente por visão
            else
            {
                fprintf(stdout, "NV\n"); // operação de leitura antes uma operação de escrita, não é equivalente por visão
            }
        }
        free(escalonamento);
    }
    return 0;
}