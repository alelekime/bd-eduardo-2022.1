#ifndef __AGENDAMENTOS__
#define __AGENDAMENTOS__

// Estrura para armazenar os dados de uma transação
typedef struct
{
	int timestamp;			// timestamp de entrada da transação
	int id_transacao;		// id da transação
	char operacao;			// operação realizada
	char item;				// item de dados maniṕulado na operação
} transacao;

// Vetor para armazenar um conjunto de transações de um agendamento
typedef transacao * agendamento;

// FUNÇÕES
int contaTransacoes(agendamento S, int num_linhas);

#endif