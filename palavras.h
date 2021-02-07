#ifndef PALAVRAS_H_INCLUDED
#define PALAVRAS_H_INCLUDED

/* 
** Header palavras.h
**
** Protótipos das funções implementadas no módulo palavras.c,
** que servem manipular as palavras do jogo Anagra-me
*/

/*
**---------------------------------------------------------------------------------------
**                                       Funções
**---------------------------------------------------------------------------------------
*/

char* escolher_Palavra (char dificuldade[11], int tam);    // Função responsável por sortear uma palavra aleatória com um tamanho estabelecido

                                                // Função responsável por fazer uma série de validações nas palavras digitadas pelo usuário
int validar_Palavra(FILE *arquivo, char *palavra_proc, int tam, char *letras_Disponiveis, int acertos, char *palavras_pontuadas[]);

                                                // Função responsável por armazenar palavras válidas digitadas pelo usuário
int guarda_Palavra_Valida(char *palavras_pontuadas[], int cont_palavras, char *palavra);

                                                // Função responsável por calcular a pontuação do jogador ao final da partida
int calcular_Pontuacao(char* palavras_pontuadas[], int cont_palavras)

#endif //PALAVRAS_H_INCLUDED