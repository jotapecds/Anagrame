#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "anagrame.h"
#include "palavras.c"

/* 
** Módulo anagrame.c
**
** Responsável por conter o fonte de todas as 
** funçoes do jogo Anagra-me
*/

/*-------------------------------------------------------------------
                            inicializa
-------------------------------------------------------------------*/
int inicializar()
{
    system("color 0A");
	jogo = (_PLAYER *) calloc(10, sizeof(_PLAYER));
	num_jogos = 0;
    cabecalho();
    return 0;
}

/*-------------------------------------------------------------------
                            Processa
-------------------------------------------------------------------*/
void processar()
{
    mostrar_Menu();
}

/*-------------------------------------------------------------------
                            Termina
-------------------------------------------------------------------*/
void terminar()
{
    puts("\n\n\t\t\t\t >>>> Ate mais! volte sempre! <<<<");
    Sleep(1500);
    system("color 0F");
    LIMPAR_TELA;
}

/*-------------------------------------------------------------------
                            Cabeçalho
-------------------------------------------------------------------*/
void cabecalho()
{
    LIMPAR_TELA;
    puts("\n\n");
    puts("\t\t |--------|    |\\      |    |--------|  |---------|    |----------|   |--------|       |\\       /|    |--------|       ");
    puts("\t\t |        |    | \\     |    |        |  |              |          |   |        |       |  \\   /  |    |               ");
    puts("\t\t |        |    |  \\    |    |        |  |              |\\         |   |        |       |   \\ /   |    |               ");
    puts("\t\t |--------|    |   \\   |    |--------|  |   |-----|    |  \\-------|   |--------|  ===  |    v    |    |--------|       ");
    puts("\t\t |        |    |    \\  |    |        |  |         |    |    \\         |        |       |         |    |               ");
    puts("\t\t |        |    |     \\ |    |        |  |         |    |      \\       |        |       |         |    |               ");
    puts("\t\t |        |    |      \\|    |        |  |---------|    |        \\     |        |       |         |    |--------|      "); 

}


/*-------------------------------------------------------------------
                    Mostra menu de opções
-------------------------------------------------------------------*/
void mostrar_Menu (void)
{
    char op;
    do
    {
        cabecalho();
        limpa_buffer();
        puts("\n\n\n\n\t\t >>> Suas opcoes sao: \n");
        puts("\t\t\t (J) >> Jogar <<");
        puts("\t\t\t (R) >> Consultar a tabela de recordes <<");
        puts("\t\t\t (A) >> Ajuda <<");
        puts("\t\t\t (S) >> Sair  <<");    
        puts("\n\t\t >>> O que deseja? ");
    
        op = toupper(getchar()); 
        switch (op)
        {
            case 'J':
                escolher_Nivel(); 
                break;
            case 'R':
                mostrar_Recordes(); 
                break;
            case 'A': 
                ajudar(); 
                break;
            case 'S': 
                break;
            default: 
                puts("\n >>> Opcao invalida <<<");
                Sleep(1500); 
                LIMPAR_TELA; 
                break;
        }
    }
    while ( (op !='J') && (op !='R') && (op !='A') && (op != 'S') );

    return;
}
/*-------------------------------------------------------------------
                Escolhe nível de dificuldade do jogo
-------------------------------------------------------------------*/
void escolher_Nivel(void)
{
    char nivel;
    do
    {
		limpa_buffer();
        //nivel = 0;
        cabecalho();
        puts("\n\n\n\n\t\t >>> Niveis de jogo: \n");
        puts("\t\t\t (1) >>  Facil  <<");
        puts("\t\t\t (2) >>  Medio  <<");
        puts("\t\t\t (3) >> Dificil <<");
        puts("\n\t\t >>> Escolha um nivel para jogar: ");
        nivel = getchar();

       switch (nivel)
       {
            case '1' : 
                jogar("nivel1.txt", 16); 
                break;
            case '2' : 
                jogar("nivel2.txt", 11); 
                break;
            case '3' : 
                jogar("nivel3.txt", 6); 
                break;
            default : 
                puts("\n >>> Opcao invalida <<<");
                Sleep(1500); 
                LIMPAR_TELA; 
                break;
        }
    }
    while( (nivel != '1') && (nivel != '2') && (nivel != '3') );
}

/*-------------------------------------------------------------------
                        Jogar partida
-------------------------------------------------------------------*/
void jogar(char dificuldade[11], int tam) 
{	
    char* palavra_Escolhida; 
    char* letras_Disponiveis;
    char* palavra;
    int cont_palavras = 0;
    char *palavras_pontuadas[200]; 
	
	puts("\n\t\t >>> Qual sera seu apelido??");
	scanf("%s", jogo[num_jogos].nome);
	
	time_t segundos = time(&segundos);
	struct tm *data_hora_atual;
	data_hora_atual = localtime(&segundos);
	*(jogo + num_jogos)->data.dia = data_hora_atual->tm_mday;
	*(jogo + num_jogos)->data.mes = data_hora_atual->tm_mon + 1;
	*(jogo + num_jogos)->data.ano = data_hora_atual->tm_year + 1900;

    if( !(palavra_Escolhida = (char*) calloc(tam, sizeof(char))) )
    {
        puts("\n >> Erro de memoria!! encerrando o jogo <<");
        Sleep(1500);
        exit(1);
    }

    if( !(letras_Disponiveis = (char*) calloc(tam, sizeof(char))) )
    {
        puts("\n >> Erro de memoria!! encerrando o jogo <<");
        Sleep(1500);
        exit(1);
    }

    if( !(palavra = (char*) calloc(tam, sizeof(char))) )
    {
        puts("\n >> Erro de memoria!! encerrando o jogo <<");
        Sleep(1500);
        exit(1);
    }

    palavra_Escolhida = escolher_Palavra( dificuldade, tam ); 
	letras_Disponiveis = ordenar ( palavra_Escolhida );
	time_t tempo = 0;
	do 
    {
		time_t segundos_i = time(&segundos_i);
		cabecalho();

		puts("\n\n\n\n\t\tAs suas letras disponiveis sao:\n\n");
        printf("\t\t\t");
		for(int i = 0; i < (tam-1); i++)
		{
			printf(" < %c > ", *(letras_Disponiveis+i));
		}
		
        limpa_buffer();
		puts("\n\n\n\n\t\t>> Monte uma palavra:\n");
		fgets(palavra, tam, stdin);

        if( (validar_Palavra( fopen("palavra.txt", "r"), palavra, tam, letras_Disponiveis, cont_palavras, palavras_pontuadas )) == 1 )
        {
            puts("\n\n\n\n\t\t>>> Sua palavra eh muito pequena!");
            getchar();
        }
        else if( (validar_Palavra( fopen("palavra.txt", "r"), palavra, tam, letras_Disponiveis, cont_palavras, palavras_pontuadas )) == 2 )
        {
            puts("\n\n\n\n\t\t>>> Você ja digitou essa palavra!");
            getchar();
        }
        else if( (validar_Palavra( fopen("palavra.txt", "r"), palavra, tam, letras_Disponiveis, cont_palavras, palavras_pontuadas )) == 3 )
        {
            puts("\n\n\n\n\t\t>>> Por favor, use somente letras disponiveis");
            getchar();
        } 
        else if( (validar_Palavra( fopen("palavra.txt", "r"), palavra, tam, letras_Disponiveis, cont_palavras, palavras_pontuadas )) == 4 )
        {
            puts("\n\n\n\n\t\t>>> Por favor, use somente a quantidade de letras disponiveis");
            getchar();
        }
        else if( (validar_Palavra( fopen("palavra.txt", "r"), palavra, tam, letras_Disponiveis, cont_palavras, palavras_pontuadas )) == 0 )
        {
            puts("\n\n\n\n\t\t>>> Palavra valida!");                
            cont_palavras = guarda_Palavra_Valida(palavras_pontuadas, cont_palavras, palavra);
            getchar();                                     
        }
		else
		{
			puts("\n\n\n\n\t\t>>> Essa palavra nao existe!");
            getchar();
		}
		time_t segundos_f = time(&segundos_f);
		tempo = tempo + (segundos_f - segundos_i);
	}
	while(tempo < 120);
	
	(jogo + num_jogos)->scores = calcular_Pontuacao(palavras_pontuadas, cont_palavras);

	printf("\n\n\n\n\t\t >>> TEMPO ESGOTADO! \n");
    Sleep(2500);

    cabecalho();
	printf("\n\n\n\n\t\t >>> Voce fez %d pontos! Muito bem!!\n\n\n", (jogo + num_jogos)->scores);
        num_jogos++;

	char op;
    do
    {
        limpa_buffer();
        puts("\n\n\n\n\t\t >>> Pressione < J > para jogar novamente, ou < M > para voltar ao menu principal: ");
        op = toupper(getchar());
        switch (op)
        { 
            case 'J':
                escolher_Nivel(); 
                break;
            case 'M': 
                mostrar_Menu(); 
                break;
            default: 
                puts("\n >>> Opcao invalida <<<");
                Sleep(1500); 
                LIMPAR_TELA; 
        }
    }
    while(op != 'J' && op !='M');
}

/*-------------------------------------------------------------------
            Mostra a tabela de pontuação dos jogadores 
-------------------------------------------------------------------*/
void mostrar_Recordes(void)
{
	cabecalho();

    if(num_jogos == 0)
    {
        puts("\n\n\n\n\t\t >>> Nenhum jogador encontrado! Jogue uma partida e resgistre sua pontuacao! <<<");
        char op;
        do
        {
            limpa_buffer();
            puts("\n\n\n\n\t\t >>> Pressione < J > para jogar, ou < M > para voltar ao menu principal: ");
            op = toupper(getchar());
            switch (op)
            { 
                case 'J':
                    escolher_Nivel(); 
                    break;
                case 'M': 
                    mostrar_Menu(); 
                    break;
                default: 
                    puts("\n >>> Opcao invalida <<<");
                    Sleep(1500); 
                    LIMPAR_TELA; 
                    break;
            }
        }
        while(op != 'J' && op !='M');  
    }

	for(int i=0; i<=num_jogos; i++)
	{
        printf("\n---------------------------------------------------------------------------------------------\n");
		printf("\n\n Nome: %s \n", jogo[i].nome);
		printf(" Data: %d/%d/%d \n", *(jogo + i)->data.dia, *(jogo + i)->data.mes, *(jogo + i)->data.ano);
		printf(" Pontuacao: %d \n\n\n", (jogo + i)->scores);
	}

    puts("\n\n\n\n\t\t >>> Pressione qualquer tecla para voltar ao menu principal: ");
    limpa_buffer();
    getchar();
    mostrar_Menu();
	return;
}

/*-------------------------------------------------------------------
                            Como Jogar 
-------------------------------------------------------------------*/
void ajudar(void)
{
    cabecalho();
    puts("\n\n\n\n\t\tAnagra-me eh um jogo cujo o objetivo eh formar o maior numero possivel de palavras                          ");
    puts("\t\tultilizando um conjunto de letras de uma palavra secreta sorteada de um dicionario.                       \n");
    puts("\t\tA cada partida uma nova palavra secreta eh sorteada, e suas letras sao embaralhadas                         ");
    puts("\t\te exibidas para a selecao. O jogador tenta entao formar varias palavras selecionando                        ");
    puts("\t\talgumas das letras disponiveis, bastando para isso, ele digitar a palavra desejada                          ");
    puts("\t\te pressionar a tecla < ENTER >.                                                                           \n");
    puts("\t\tSe a palavra digitada for valida, ou seja, se encontra no dicionario, ultiliza apenas                       ");
    puts("\t\tletras disponiveis, e nao foi digitada previamente, entao o jogador ganha pontos.                         \n");
    puts("\t\tO maior desafio do jogo eh encontar uma palavra com todas as letras disponiveis, ou seja:                   ");
    puts("\t\tadivinhar a palavra secreta que lhe foi sorteda.                                                          \n");
    puts("\t\tUma partida dura apenas dois minutos, entao, seja rapido e eficiente para ficar entre os melhores jogadores!");
    puts("\n\n\n\n\t\t >>> Pressione qualquer tecla para voltar ao menu principal:                                        ");
    limpa_buffer();
    getchar();
    mostrar_Menu();
}

void limpa_buffer(void)
{
    while(getchar() != '\n');
}