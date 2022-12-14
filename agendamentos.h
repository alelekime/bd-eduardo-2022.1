#ifndef __AGENDAMENTOS__
#define __AGENDAMENTOS__

// Estrutura para armazenar os dados de uma etapa de uma transação
typedef struct
{
	int timestamp;		// timestamp de entrada da transação
	int id_transacao;	// id da transação
	char operacao;		// operação realizada
	char item;		// item de dados maniṕulado na operação
} transacao;

// Vetor para armazenar um conjunto de transações de um agendamento
typedef transacao *agendamento;

// FUNÇÕES
int encontraOperacoes(agendamento S, int num_transacoes, char *operacoes, int *indiceOperacoes);
int equivalenciaPorVisao(agendamento *S, int num_transacoes);
int encontraEscrita(agendamento S, int num_transacoes);
int verificaEscrita(agendamento S, int idEscrita);
int contaTransacoes(agendamento S, int num_linhas);
int contaTransacoesEscalonamento(agendamento S, int num_linhas);
int contaTransacoesEmCiclos(int *ciclos, int num_transacoes);
int *transacoesConflitantes(int *ciclos, int num_transacoes, int num_ciclos);
int *transacoesSerializaveis(int *ciclos, int num_transacoes, int num_ciclos);

#endif
