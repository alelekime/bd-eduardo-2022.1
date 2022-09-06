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
    int num_linhas = 0, num_transacoes = 0, num_escalonamentos = 0;
    agendamento S = NULL;

    num_linhas = leAgendamentos(stdin, &S);
    printf("Número de linhas da entrada: %d\n", num_linhas); // APAGAR DEPOIS
    num_transacoes = contaTransacoes(S, num_linhas);
    printf("Número de transações do agendamento: %d\n", num_transacoes); // APAGAR DEPOIS

    int timestamp_limite[num_transacoes];
    for (int i = 0; i < num_transacoes; i++)
        timestamp_limite[i] = 0;


    // laço que percorre o agendamento S com as transações da entrada para identificar todos os escalonamentos
    for (int i = 0; i < num_linhas; i++)
    {
        if ((S[i].operacao == 'C') && ((i + 1 == num_linhas) || (S[i + 1].operacao != 'C')))
        {
            timestamp_limite[num_escalonamentos] = S[i].timestamp; 
            num_escalonamentos++;
        }
    }

    // APAGAR DEPOIS
    for (int i = 0; i < num_escalonamentos; i++)
    {
        printf("Escalonamento %d termina no timestamp %d\n", i + 1, timestamp_limite[i]);
    }

    


    grafo *grafo_transacoes = criaGrafoTransacoes(S, num_linhas, num_transacoes);
    printf("Criou o grafo.\n"); // APAGAR DEPOIS

    int *ciclos = buscaCiclosTransacoes(grafo_transacoes);                      
    int num_transacoes_ciclos = contaTransacoesEmCiclos(ciclos, num_transacoes);
    printf("Número de transações em ciclos: %d\n", num_transacoes_ciclos); // APAGAR DEPOIS
    int *transacoes_conflitantes = transacoesConflitantes(ciclos, num_transacoes, num_transacoes_ciclos);
    int *transacoes_serializaveis = transacoesSerializaveis(ciclos, num_transacoes, num_transacoes_ciclos);

    return 0;
}
