#ifndef PALAVRAS_H_INCLUDED
#define PALAVRAS_H_INCLUDED

/* 
* Header palavras.h
*
* Protótipos das funções implementadas no módulo palavras.c,
* que servem manipular as palavras do jogo Anagra-me
*/

/*
**---------------------------------------------------------------------------------------
**                                       Funções
**---------------------------------------------------------------------------------------
*/

/* Função responsável por sortear uma palavra aleatória com um tamanho estabelecido */
char* escolher_palavra (char dificuldade[11], int tam);

/* Função responsável por fazer uma série de validações nas palavras digitadas pelo usuário */
int validar_palavra(char *palavra_proc, int tam, char *letras_Disponiveis, char *palavras_pontuadas[], int acertos);

/* Função responsável por armazenar palavras válidas digitadas pelo usuário */
int guarda_palavra_valida(char *palavra, char *palavras_pontuadas[], int cont_palavras);

/* Função responsável por calcular a pontuação do jogador ao final da partida */
int calcular_pontuacao(char* palavras_pontuadas[], int cont_palavras);

#endif //PALAVRAS_H_INCLUDED