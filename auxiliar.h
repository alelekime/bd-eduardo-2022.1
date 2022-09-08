#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "agendamentos.h"
#include "grafos.h"

#define LIMITE 100

#ifndef __AUXILIAR__
#define __AUXILIAR__

// FUNÇÕES
void testeIniniciacao(bool teste, const char *descricao);
int leAgendamentos(FILE *input, agendamento *S);
void imprimeIDs(agendamento S, int num_linhas, int num_transacoes);

#endif 