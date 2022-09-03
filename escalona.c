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

int main() 
{
    int num_linhas = 0;
    agendamento S = NULL;

    num_linhas = leAgendamento(stdin, &S);
    printf("%d\n", num_linhas); // APAGAR DEPOIS

    return 0;
}
