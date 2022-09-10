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
void imprimeIDs(agendamento S, int num_linhas);

#endif