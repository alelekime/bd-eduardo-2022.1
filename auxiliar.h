#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef __AUXILIAR__
#define __AUXILIAR__

#define LIMITE 100

// FUNÇÕES
void testaInicializacao(bool teste, char *descricao);
int leAgendamentos(FILE *input, agendamento *S);
int cmpfunc(const void *a, const void *b);
    void imprimeIDs(agendamento escalonamento, int num_linhas, int num_transacoes);
#endif