#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "auxiliar.h"


int leAgendamento(FILE *input, agendamento *S) 
{
	int i = 0, limite = 40;
	*S = (agendamento) malloc(sizeof (transacao) * limite);

	while (fscanf(input, "%d %d %c %c\n", &(*S)[i].timestamp, &(*S)[i].id_transacao, &(*S)[i].operacao, &(*S)[i].item) == 4)
	{
		i++;
		if (i >= limite)
		{
			limite += 5;
			*S = (agendamento) realloc(*S, sizeof (transacao) * limite);
		}
	}
	*S = (agendamento) realloc(*S, sizeof (transacao) * i);
	return i;
}