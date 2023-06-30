#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED

/* 
* Header threading.h
*
* Protótipos das funções implementadas no módulo threading.c,
* que forcecem suporte a multi threading para os outros módulos.
*/

/*
**---------------------------------------------------------------------------------------
**                                       Estruturas
**---------------------------------------------------------------------------------------
*/

// Estrutura cujo objetivo é armazenar os argumentos para a função thread
typedef struct
{
    // Thread ID
    int tid;
    // Palavra buscada
    char* palavra;
}_ARGS;

/*
**---------------------------------------------------------------------------------------
**                                       Variáveis
**---------------------------------------------------------------------------------------
*/

// Número de threads. Valor default: 4
int num_threads = 4;
// Booleano que indica se a palavra foi achada. Valor default: 0 (Não achou)
int achou = 0;

/*
**---------------------------------------------------------------------------------------
**                                       Funções
**---------------------------------------------------------------------------------------
*/

/*
*  Função thread: busca pela palavra no dicionário.
*/
void* busca_palavra (void* args);

/*
* Função cujo objetivo é validar se a palavra fornecida existe no dicionario.
* 
* Retorno: 
*   0 -> Caso a palavra exista;
*   5 -> Caso a palavra não exista;
*/
int validar_palavra_existente(char* palavra);

#endif //THREADING_H_INCLUDED