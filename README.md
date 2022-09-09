<h1>Escalonamento de transações</h1>

Implementação, em C, dos algoritmos de teste de serialidade quanto ao conflito e de visão equivalente para detecção de conflitos de escalonamento de transações concorrentes em SGBD. Trabalho desenvolvido por Alessandra Souza da Silva e Marisa Sel Franco para a disciplina CI1218 - Bancos de Dados, ministrada pelo prof. Eduardo Almeida, dos cursos de bacharelado em Ciência da Computação e em Informática Biomédica da UFPR. 


## Algoritmo de teste de seriabilidade quanto ao conflito:
  
- Crie um nó para cada T do escalonamento S;
- Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti;
- Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti;
- Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti;
- S é serial se não existe ciclo no grafo.

## Algoritmo de visão equivalente:

Dois agendamentos S e S' são ditos visão equivalentes se atenderem às seguintes condições:
- O mesmo conjunto de transações e operações participam em S e S';
- Para cada r(x) de Ti, se o valor de x lido ja foi escrito por w(x) de Tj, ou seja, houve w(x) antes de r(x) em transações distintas, a mesma coisa deve acontecer para r(x) de Ti em S';
- Se o operador w(y) em Tk é a última escrita de y em S, então w(y) em Tk deve ser a última escrita em S'.

## Bibliotecas utilizadas

:warning: [stdio.h](https://www.tutorialspoint.com/c_standard_library/stdio_h.htm)
  
:warning: [stdlib.h](https://www.tutorialspoint.com/c_standard_library/stdio_h.htm?key=stdlib.h)
  
:warning: [string.h](https://www.tutorialspoint.com/c_standard_library/string_h.htm)

## Como compilar

No terminal, execute: 

```
make
```

## Como rodar

No terminal, execute: 

```
./escalona < teste.in > teste.out
```
## Entrada:
A entrada é feita pela entrada padrão (stdin). O arquivo é formado por uma sequência de linhas, em que cada linha representa uma transação chegando. Cada linha tem quatro campos: o primeiro é o tempo de chegada, o segundo é o identificador da transação, o terceiro é a operação (R=read, W=write, C=commit) e o quarto o atributo que será lido/escrito. Estas linhas estão ordenadas pelo primeiro campo (tempos menores no início indicando a linha do tempo).

## Saída:
A saída é feita pela saída padrão (stdout). O arquivo é composto por uma sequência de linhas, sendo uma linha para cada escalonamento. Cada linha tem quatro campos separados por espaço (um único espaço entre cada par de campos). O primeiro campo é o identificador do escalonamento. O segundo campo é a lista de transações. E o terceiro apresenta o resultado do algoritmo da garantia da seriabilidade, em que SS e NS significam respectivamente serial (SS) ou não serial (NS). O quarto campo é o resultado do algoritmo de teste de equivalência de visão, em que SV e NV significam respectivamente equivalente (SV) ou não equivalente (NV).
