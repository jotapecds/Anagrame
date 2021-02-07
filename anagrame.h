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

typedef struct                                   // Estrutura DATA
{
    char dia[3];
    char mes[3];
    int ano[5];
}_DATA;

typedef struct                                   // Estrutura PLAYER, para armazenar nome do jogador, sua pontuação e a data da partida
{
    char nome[20];
    int scores;
    _DATA data;
}_PLAYER;

/*
**---------------------------------------------------------------------------------------
**                                    Variáveis globais
**---------------------------------------------------------------------------------------
*/

_PLAYER *jogo;                                   // Estruturas com os dados nomes, pontuações e datas das partidas dos jogadores
int num_jogos;                                   // Quantidade de partidas executadas


/*
**---------------------------------------------------------------------------------------
**                                       Funções
**---------------------------------------------------------------------------------------
*/

int inicializar();                               // Função responsável por preparar todo o ambiente para que o jogo se inicie 

void processar();                                // Função responsável por processar todos os dados do jogo e das partidas

void terminar();                                 // Função responsável por encerrar todas as tarefas e finalizar o programa

void cabecalho();                                // Função responsável por exibir um cabeçalho na tela para o usuário

void mostrar_Menu (void);                        // Função responsável por exibir o menu principal de opções do jogo para o usuário

void escolher_Nivel(void);                       // Função responsável por exibir um menu com os níveis de jogo para o usuário

void jogar(char dificuldade[11], int tam);       // Função responsável pela partida em si

void ajudar(void);                               // Função responsável por exibir um texto informativo ao usuário

void mostrar_Recordes(void);                     // Função responsável por exibir os records dos jogadores

void limpa_buffer(void);                         // Função responsável por limpar o buffer do teclado

#endif //ANAGRAME_H_INCLUDED