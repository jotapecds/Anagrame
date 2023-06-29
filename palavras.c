#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <regex.h>
#include "anagrame.h"

/* 
** Módulo palavras.c
**
** Responsável por conter o fonte de todas as funçoes
** de malipulação das palavras do jogo Anagra-me
*/

char* escolher_palavra (char dificuldade[11], int tam)
{
    // String contendo uma palavra escolhida aleatoriamente do nível desejado
    char *palavra_escolhida;
    // Inteiro contendo um index aleatório para ler uma palavra nos arquivos de nível 
    int n;
    // Variável RegEx para validação da palavra escolhida
    regex_t regex;

    FILE* arq = fopen(dificuldade, "r");
    if(!arq) 
    {
        puts("Erro na leitura do arquivo!! Encerrando o jogo.");
        exit(1);
    }

    if( !(palavra_escolhida = (char*) calloc(tam, sizeof(char))) )
    {
        puts("Erro de memoria!! Encerrando o jogo.");
        exit(1);
    }

    if( regcomp(&regex, "[:alpha:]", 0) != 0 ) // Compilando um padrão com apenas letras maiúsculas e minúsculas
    {
        puts("Falha ao compilar o RegEx!! Encerrando o jogo.");
        exit(1);
    }

    srand((unsigned) time(NULL)); 
    n = tam * (rand() % 20);  // Delimita o index até a 5000ª palavra do arquivo

    fseek(arq, n, SEEK_SET);
    fgets(palavra_escolhida, tam, arq);

    //puts(palavra_escolhida);
    // for(int i = 0; i < tam; i++)
    // {
    //     if( regexec(&regex, palavra_escolhida, 0, NULL, 0) != 0) 
    //     {
    //         puts("entrei na recursao");
    //         palavra_escolhida = escolher_palavra( dificuldade, tam );
    //         break;
    //     }
    // }
    
	fclose(arq);
    return palavra_escolhida;
}

int validar_palavra(char *palavra_proc, int tam, char *letras_Disponiveis, char *palavras_pontuadas[], int acertos)
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
    for (int i = 0; i < TAM_DIC; i++)
    {
        if( strcmp(palavra_proc, dicionario[i]) == 0 ){
            return 0;
        }
    }

	return 5;
}

int guarda_palavra_valida(char *palavra, char *palavras_pontuadas[], int cont_palavras)
{   
    if ( !(palavras_pontuadas[cont_palavras] = (char*) calloc(strlen(palavra), sizeof(char)))) // alocação do vetor que guarda as palavras
    {
         puts("\n\nErro ");          
         exit(1);
    } 
            
    strcpy( *(palavras_pontuadas+ cont_palavras), palavra ); //Salvando palavra no vetor alocado       
    
    return ++cont_palavras;        
}

char* ordenar_alfabeticamente (char *palavra_Escolhida)
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

int calcular_pontuacao(char* palavras_pontuadas[], int cont_palavras)
{   
	int pontuacao = 0;
	for(int i = 0; i < cont_palavras; i++)
	{
		pontuacao = pontuacao + ((strlen(palavras_pontuadas[i])-1) * 5);
	}
	return pontuacao;
}
