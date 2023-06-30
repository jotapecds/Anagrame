#ifndef ANAGRAME_H_INCLUDED
#define ANAGRAME_H_INCLUDED

/* 
** Header anagrame.h
**
** Estruturas, variáveis globais e protótipos das funções implementadas no módulo
** anagrame.c, que servem executar o jogo Anagra-me
*/

#ifdef WIN32
#define LIMPAR_TELA system("cls")
#include <windows.h>
#else
#define LIMPAR_TELA system("clear")
#include <unistd.h>
#endif //WIN32

/*
**---------------------------------------------------------------------------------------
**                                      Estruturas
**---------------------------------------------------------------------------------------
*/

// Estrutura DATA
typedef struct
{
    char dia[3];
    char mes[3];
    int ano[5];
}_DATA;

// Estrutura PLAYER, para armazenar nome do jogador, sua pontuação e a data da partida
typedef struct
{
    char nome[20];
    int scores;
    _DATA data;
}_PLAYER;

/*
**---------------------------------------------------------------------------------------
**                           Definições e Variáveis globais
**---------------------------------------------------------------------------------------
*/

// Nome do arquivo com as palavras do nível 1
#define NIVEL1 "nivel1.txt"
// Nome do arquivo com as palavras do nível 2
#define NIVEL2 "nivel2.txt"
// Nome do arquivo com as palavras do nível 3
#define NIVEL3 "nivel3.txt" 
// Nome do arquivo de dicionário
#define DICIONARIO "dicionario.txt"
// Quantidade de palavras no dicionário
#define TAM_DIC 320076

// Estruturas com os dados nomes, pontuações e datas das partidas dos jogadores
_PLAYER *jogo;
// Quantidade de partidas executadas
int num_jogos;                                   
// Vetor que armazena todas as palavras do dicionário
char* dicionario[TAM_DIC];

/*
**---------------------------------------------------------------------------------------
**                                       Funções
**---------------------------------------------------------------------------------------
*/

/* Função responsável por preparar todo o ambiente para que o jogo se inicie. */
int inicializar(void); 

/* 
* Função responsável por iniciar e distribuir o fluxo de execução de acordo com a opção. 
*
* op -> indica a opção de processamento: 
*       (0) -> Padrão: Exibir menu inicial;
*       (1) -> Customizado: Iniciar partida no nível 1;
*       (2) -> Customizado: Iniciar partida no nível 2;
*       (3) -> Customizado: Iniciar partida no nível 3;
*       (4) -> Customizado: Iniciar testes de desempenho;
*/
void processar(int op);

/* Função responsável por encerrar todas as tarefas e finalizar o programa. */
void terminar(void);

/*
* Função responsável por imprimir o cabeçalho do jogo na tela.
* 
* op -> indica a opção de cabeçalho: 
*       (0) Cabeçalho padrão;
*       (1) Cabecalho customizado;
*/
void exibir_cabecalho(int op);

/* Função responsável por exibir o menu principal de opções do jogo para o usuário */
void exibir_menu(void);

/* Função responsável por exibir um menu com os níveis de jogo para o usuário */
void escolher_nivel(void);

/* Função que dá início e controla uma nova partida */
void jogar(char dificuldade[11]);

/* Função responsável por exibir um texto informativo ao usuário */
void exibir_ajuda(void);

/* Função responsável por exibir os records dos jogadores */
void exibir_recordes(void);

/* Realiza buscas de palavras no dicionário comparando as versões sequêncial e concorrente */
void testar_desempenho(void);

/* Função responsável por limpar o buffer do teclado */
void limpa_buffer(void);

#endif //ANAGRAME_H_INCLUDED