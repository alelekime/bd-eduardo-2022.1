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
    int num_linhas = 0, num_transacoes = 0;
    agendamento S = NULL;

    num_linhas = leAgendamento(stdin, &S);
    printf("Número de linhas do agendamento: %d\n", num_linhas); // APAGAR DEPOIS
    num_transacoes = contaTransacoes(S, num_linhas);
    printf("Número de transações do agendamento: %d\n", num_transacoes); // APAGAR DEPOIS

    grafo *grafo_transacoes = criaGrafoTransacoes(S, num_linhas, num_transacoes);
    printf("Criou o grafo.\n"); // APAGAR DEPOIS
    return 0;
}
