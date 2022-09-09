/*  T2 CI-218 - Sistemas de Banco de Dados - UFPR
 *   Orientação: prof. Dr. Eduardo Almeida
 *   Autoras:
 *           Alessandra Souza da Silva   GRR20182558
 *           Marisa Sel Franco           GRR20186556
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "auxiliar.h"
#include "grafos.h"

int main()
{
    int id, num_linhas = 0, num_transacoes = 0, num_escalonamentos = 0, num_linhas_escalonamento = 0, inicio = 0;
    agendamento S = NULL;

    num_linhas = leAgendamentos(stdin, &S);
    // printf("Número de linhas da entrada: %d\n", num_linhas); // APAGAR DEPOIS
    num_transacoes = contaTransacoes(S, num_linhas);
    // printf("Número de transações do agendamento: %d\n", num_transacoes); // APAGAR DEPOIS

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
        if (!escalonamento)
        {
            fprintf(stderr, "Erro: não foi possível alocar escalonamento.\n");
            exit(-4);
        }
        for (int i = inicio, j = 0; i < (num_linhas + inicio); i++, j++)
        {
            escalonamento[j].timestamp = S[i].timestamp;
            escalonamento[j].id_transacao = S[i].id_transacao;
            escalonamento[j].operacao = S[i].operacao;
            escalonamento[j].item = S[i].item;
        }

        /*printf("Escalonamento %d tem %d linhas\n\n", id, num_linhas_escalonamento); // APAGAR DEPOIS
        for (int i = 0; i < num_linhas_escalonamento; i++){
            printf("%d %d %c %c \n", escalonamento[i].timestamp, escalonamento[i].id_transacao, escalonamento[i].operacao, escalonamento[i].item);
        }*/
        num_transacoes = contaTransacoesEscalonamento(escalonamento, num_linhas_escalonamento);
        // printf("Número de transações do escalonamento: %d\n", num_transacoes); // APAGAR DEPOIS
        grafo *grafo_transacoes = criaGrafoTransacoes(escalonamento, num_linhas_escalonamento, num_transacoes);
        int *ciclos = buscaCiclosTransacoes(grafo_transacoes);
        int num_transacoes_ciclos = contaTransacoesEmCiclos(ciclos, num_transacoes);
        // printf("No escalonamento %d, há %d transações que fazem parte de ciclos\n\n\n", id, num_transacoes_ciclos);  // APAGAR DEPOIS
        
        // se o grafo NÃO tem CICLOS
        if (num_transacoes_ciclos == 0)
        {
            fprintf(stdout, "%d ", id);
            imprimeIDs(escalonamento, num_linhas_escalonamento);
            fprintf(stdout, " SS SV\n"); // o agendamento é serializável por conflito e por visão
        }
        // se o grafo TEM CICLOS
        else
        {
            // análise da serialidade por conflito
            fprintf(stdout, "%d ", id);
            imprimeIDs(escalonamento, num_linhas_escalonamento);
            fprintf(stdout, " NS "); // o agendamento NÃO é serializável por conflito
            int verificaEscritaTrasacao;
            int idEscrita = encontraEscrita(S, num_transacoes);
            if (idEscrita == -1)
                fprintf(stdout, " SV "); // o agendamento é equivalente por visão
            else
            {
                verificaEscritaTrasacao = verificaEscrita(S, idEscrita);

            }

            fprintf(stdout, "\n"); // APAGAR APÓS INSERIR ANÁLISE E SAÍDA DA EQUIVALÊNCIA POR VISÃO
        }
        free(escalonamento);
    }
    return 0;
}