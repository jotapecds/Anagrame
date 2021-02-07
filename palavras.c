#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "anagrame.h"

/* 
** Módulo palavras.c
**
** Responsável por conter o fonte de todas as funçoes
** de malipulação das palavras do jogo Anagra-me
*/

char* escolher_Palavra (char dificuldade[11], int tam)
{
    char *palavra_Escolhida;
    int n;

    FILE* arq = fopen(dificuldade, "r");
    if(!arq) 
    {
        puts("Erro na leitura do arquivo!! Encerrando o jogo.");
        exit(1);
    }

    if( !(palavra_Escolhida = (char*) calloc(tam, sizeof(char))) )
    {
        puts("Erro de memoria!! Encerrando o jogo.");
        exit(1);
    }

    srand((unsigned) time(NULL)); 
    n = 0 + (rand()) % 20; // as linhas vão de 0 até 20
    // configurando o n para a fseek funcionar
    n = n*(tam + 1);
    
    fseek(arq, n, SEEK_SET);
    fgets(palavra_Escolhida, tam, arq);

    for(int i = 0; i < tam; i++)
    {
        if( (palavra_Escolhida[i] == 32) || (palavra_Escolhida[i] == 45) ) 
        {
            escolher_Palavra( dificuldade, tam );
        }
           
    }
    
	fclose(arq);
    return palavra_Escolhida;
}

int validar_Palavra(FILE *arquivo, char *palavra_proc, int tam, char *letras_Disponiveis, int acertos, char *palavras_pontuadas[])
{
    //A FUNÇÃO RETORNA ZERO SE A PALAVRA É VÁLIDA
    char palavra_test[tam];
    char guarda_letras_Disponiveis[tam];
    int count = 0;

    // Validação do tamanho da palavra
    if( (strlen(palavra_proc)) <= 3 ) 
        return 1;
   
    // Validando se a palavra já foi digitada pelo usuário
    if (acertos >= 1)      
        for (int i = 0; i < acertos; i++)
            if( (strcmp(palavra_proc, palavras_pontuadas[i])) == 0)
                return 2;

    // Validando se a palavra digitada tem alguma letra indisponível
    for(int i = 0; i < strlen(palavra_proc); i++)
		for(int j = 0; j < (tam-1); j++)
			if(palavra_proc[i] == letras_Disponiveis[j])
			{
				count++;
				j = (tam-1);
			}
    if(count != strlen(palavra_proc)-1)
        return 3;

    // Validando se a palavra digitada tem letras repetidas
    for(int i = 0; i < tam; i++)
        guarda_letras_Disponiveis[i] = letras_Disponiveis[i];

    for (int i=0; i < strlen(palavra_proc)-1; i++)
    {
        for (int j =0; j < tam; j++)
        {
            if (palavra_proc[i] == letras_Disponiveis[j])
            {
                letras_Disponiveis[j] = '*';
                break;
            }
            if (letras_Disponiveis[j] =='\0') 
            {
                for(int i = 0; i < tam; i++)
                    letras_Disponiveis[i] = guarda_letras_Disponiveis[i];
                return 4;                       
            }
        }
    }
    for(int i = 0; i < tam; i++)
        letras_Disponiveis[i] = guarda_letras_Disponiveis[i];
    
    // Validando se a palavra existe no dicionário
    fseek(arquivo, 0, SEEK_SET); 
    while ( !feof(arquivo) )
    {
        fgets(palavra_test, tam, arquivo);
        if( (strcmp(palavra_proc, palavra_test) == 0) ){
            return 0;
			fclose(arquivo);
		}
    }
	fclose(arquivo);
	return 5;
}

int guarda_Palavra_Valida(char *palavras_pontuadas[], int cont_palavras, char *palavra)
{   
    if ( !(palavras_pontuadas[cont_palavras] = (char*) calloc(strlen(palavra), sizeof(char)))) // alocação do vetor que guarda as palavras
    {
         puts("\n\nErro ");          
         exit(1);
    } 
            
    strcpy( *(palavras_pontuadas+ cont_palavras), palavra ); //Salvando palavra no vetor alocado       
    
    return ++cont_palavras;        
}

char* ordenar (char *palavra_Escolhida)
{
    // ordenando a palavra de forma alfebetica 

	*palavra_Escolhida = tolower(*palavra_Escolhida);
    for (int i = 0; i < (strlen(palavra_Escolhida)-1); i++)
    {
        for (int j = (i + 1); j < (strlen(palavra_Escolhida)); j++)
        {
            if (palavra_Escolhida[i] > palavra_Escolhida[j])
            {
                char aux = palavra_Escolhida[i];
                palavra_Escolhida[i] = palavra_Escolhida[j];
                palavra_Escolhida[j] = aux;

            }
        }
    }
    return palavra_Escolhida;
}

int calcular_Pontuacao(char* palavras_pontuadas[], int cont_palavras)
{   
	int pontuacao = 0;
	for(int i = 0; i < cont_palavras; i++)
	{
		pontuacao = pontuacao + ((strlen(palavras_pontuadas[i])-1) * 5);
	}
	return pontuacao;
}
