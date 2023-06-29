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

    num_jogos = 0;
    jogo = (_PLAYER *) calloc(10, sizeof(_PLAYER));

    if(jogo == NULL || dicionario == NULL)
    {
        puts("\n\n>>> Falha na alocação de memória. Encerrando a execução.");
        return -1;
    }

    FILE* arq = fopen("dicionario.txt", "r");
    if( arq == NULL )
    {
        puts("\n\n>>> Falha ao abrir o arquivo < dicionario.txt >. Encerrando a execução.");
        return -1;
    }

    char palavra[50]; 
    int i = 0;
    // Lê cada palavra do arquivo e armazena no vetor
    while (fgets(palavra, 50, arq) != NULL && i < TAM_DIC) 
    {
        dicionario[i] = malloc(strlen(palavra) + 1);
        strcpy(dicionario[i], palavra);
        i++;
    }

	fclose(arq);
    return 0;
}

/*-------------------------------------------------------------------
                            Processa
-------------------------------------------------------------------*/
void processar(int op)
{
    switch (op)
    {
        case 0:
            exibir_menu();
            break;
        case 1: 
            jogar(NIVEL1); 
            break;
        case 2:
            jogar(NIVEL2); 
            break;
        case 3: 
            jogar(NIVEL3); 
            break;
        default: 
            exibir_menu();
            break;
    }
}

/*-------------------------------------------------------------------
                            Termina
-------------------------------------------------------------------*/
void terminar()
{
    for (int i = 0; i < TAM_DIC; i++) {
        free(dicionario[i]);
    }

    puts("\n\n>>> Ate mais! volte sempre!");
    sleep(2);
    system("color 0F");
    LIMPAR_TELA;
}

/*-------------------------------------------------------------------
                            Cabeçalho
-------------------------------------------------------------------*/
void exibir_cabecalho(int op)
{
    if(op == 1)
    {
        LIMPAR_TELA;
        puts("\n\n");
        puts("\t|--------|");
        puts("\t|        |");
        puts("\t|        |");
        puts("\t|--------|");
        puts("\t|        |");
        puts("\t|        |");
        puts("\t|        |");
        sleep(1);
        LIMPAR_TELA;
        puts("\n\n");
        puts("\t|--------|    |\\      |    |--------|");
        puts("\t|        |    | \\     |    |        |");
        puts("\t|        |    |  \\    |    |        |");
        puts("\t|--------|    |   \\   |    |--------|");
        puts("\t|        |    |    \\  |    |        |");
        puts("\t|        |    |     \\ |    |        |");
        puts("\t|        |    |      \\|    |        |"); 
        sleep(1);
        LIMPAR_TELA;
        puts("\n\n");
        puts("\t|--------|    |\\      |    |--------|  |---------|    |----------|   |--------| ");
        puts("\t|        |    | \\     |    |        |  |              |          |   |        | ");
        puts("\t|        |    |  \\    |    |        |  |              |\\         |   |        |");
        puts("\t|--------|    |   \\   |    |--------|  |   |-----|    |  \\-------|   |--------|");
        puts("\t|        |    |    \\  |    |        |  |         |    |    \\         |        |");
        puts("\t|        |    |     \\ |    |        |  |         |    |      \\       |        |");
        puts("\t|        |    |      \\|    |        |  |---------|    |        \\     |        |"); 
        sleep(2);
    } 
    // 
    LIMPAR_TELA;
    puts("\n\n");
    puts("\t|--------|    |\\      |    |--------|  |---------|    |----------|   |--------|       |\\       /|    |--------|   ");
    puts("\t|        |    | \\     |    |        |  |              |          |   |        |       |  \\   /  |    |            ");
    puts("\t|        |    |  \\    |    |        |  |              |\\         |   |        |       |   \\ /   |    |           ");
    puts("\t|--------|    |   \\   |    |--------|  |   |-----|    |  \\-------|   |--------|  ===  |    v    |    |--------|   ");
    puts("\t|        |    |    \\  |    |        |  |         |    |    \\         |        |       |         |    |            ");
    puts("\t|        |    |     \\ |    |        |  |         |    |      \\       |        |       |         |    |            ");
    puts("\t|        |    |      \\|    |        |  |---------|    |        \\     |        |       |         |    |--------|   ");
    sleep(1);
}


/*-------------------------------------------------------------------
                    Mostra menu de opções
-------------------------------------------------------------------*/
void exibir_menu(void)
{
    char op;
    do
    {
        exibir_cabecalho(1);
        limpa_buffer();
        puts("\n\n>>> Suas opcoes sao:");
        puts("\n\t(J) >> Jogar <<");
        puts("\t(R) >> Consultar a tabela de recordes <<");
        puts("\t(A) >> Ajuda <<");
        puts("\t(S) >> Sair  <<");    
        puts("\n>>> O que deseja? ");
    
        op = toupper(getchar()); 
        switch (op)
        {
            case 'J':
                escolher_nivel(); 
                break;
            case 'R':
                exibir_recordes(); 
                break;
            case 'A': 
                exibir_ajuda(); 
                break;
            case 'S': 
                break;
            default: 
                puts("\n>>> Opcao invalida <<<");
                sleep(2); 
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
void escolher_nivel(void)
{
    char nivel;
    do
    {
		limpa_buffer();
        exibir_cabecalho(0);
        puts("\n\n>>> Niveis de jogo: \n");
        puts("\t(1) >>  Facil  <<");
        puts("\t(2) >>  Medio  <<");
        puts("\t(3) >> Dificil <<");
        puts("\n>>> Escolha um nivel para jogar: ");
        nivel = getchar();

       switch (nivel)
       {
            case '1' : 
                jogar(NIVEL1); 
                break;
            case '2' : 
                jogar(NIVEL2); 
                break;
            case '3' : 
                jogar(NIVEL3); 
                break;
            default : 
                puts("\n >>> Opcao invalida <<<");
                sleep(2); 
                LIMPAR_TELA; 
                break;
        }
    }
    while( (nivel != '1') && (nivel != '2') && (nivel != '3') );
}

/*-------------------------------------------------------------------
                        Jogar partida
-------------------------------------------------------------------*/
void jogar(char dificuldade[11]) 
{
    exibir_cabecalho(0);
    
    // String contendo as letras sorteadas e disponibilizadas ao usuário.
    char* letras_disponiveis;
    // String contendo a tentativa de palavra inserida pelo usuário a ser validada.
    char* palavra_inserida;
    // Vetor de strings contendo todas as palavras já validadas.
    char* palavras_pontuadas[200]; 
    // Inteiro que controla a quantidade de palavras já validadas.
    int cont_palavras = 0;
    // Inteiro que contém o tamanho máximo das palavras do nível atual
    int tam;

    if(dificuldade == NIVEL1)
        tam = 16;
    else if(dificuldade == NIVEL2)
        tam = 11;
    else if(dificuldade == NIVEL3)
        tam = 6;
    else
    {
        puts("\n\n>>> Opção de nível não é válida. Finalizando execução.");
        sleep(3);
        exit(1);        
    }

    letras_disponiveis = (char*) calloc(tam, sizeof(char));
    palavra_inserida = (char*) calloc(tam, sizeof(char));

    if(!letras_disponiveis || !palavra_inserida)
    {
        puts("\n\n>>> Falha na alocação de memória. Encerrando a execução.");
        sleep(3);
        exit(1);
    }

	letras_disponiveis = ordenar_alfabeticamente(escolher_palavra(dificuldade, tam));

	time_t segundos = time(NULL);
	struct tm *data_hora_atual;
	data_hora_atual = localtime(&segundos);

	*(jogo + num_jogos)->data.dia = data_hora_atual->tm_mday;
	*(jogo + num_jogos)->data.mes = data_hora_atual->tm_mon + 1;
	*(jogo + num_jogos)->data.ano = data_hora_atual->tm_year + 1900;

    puts("\n>>> Qual será seu apelido? ");
	scanf("%s", jogo[num_jogos].nome);
	
    printf("\nMuito bem, %s, PREPARE-SE! Sua partida começará em 3...2...1...\n", jogo[num_jogos].nome);
    limpa_buffer();
    sleep(5);

	time_t tempo = 0;
	do 
    {
		time_t segundos_i = time(NULL);

		exibir_cabecalho(0);
		puts("\n\nAs suas letras disponiveis sao:\n");
		for(int i = 0; i < (tam-1); i++)
		{
			printf(" < %c > ", *(letras_disponiveis+i));
		}

		puts("\n\n>> Monte uma palavra:\n");
		fgets(palavra_inserida, tam, stdin);

        switch( validar_palavra(palavra_inserida, tam, letras_disponiveis, palavras_pontuadas, cont_palavras) )
        {
            case 0: 
                puts("\n\n>>> Palavra valida!");                
                cont_palavras = guarda_palavra_valida(palavra_inserida, palavras_pontuadas, cont_palavras);
                break;
            case 1:
                puts("\n\n>>> Sua palavra eh muito pequena! <<<");
                break;
            case 2:
                puts("\n\n>>> Você ja digitou essa palavra! <<<");
                break;
            case 3:
                puts("\n\n>>> Por favor, use somente letras disponiveis <<<");
                break;
            case 4:
                puts("\n\n>>> Por favor, use somente a quantidade de letras disponiveis <<<");
                break;
            case 5:
                puts("\n\n>>> Essa palavra nao existe! <<<");
                break;
            default:
    			puts("\n\n>>> Resultado inesperado! <<<");
                break;
        }

		tempo += time(NULL) - segundos_i;
        sleep(1);

	} while(tempo < 120);
	
    puts("\n\n\n\n>>> TEMPO ESGOTADO!");
    sleep(2);
    puts("\nPressione qualquer tecla para prosseguir...");
    limpa_buffer();

	(jogo + num_jogos)->scores = calcular_pontuacao(palavras_pontuadas, cont_palavras);

	char op;
    do
    {
        
        exibir_cabecalho(1);
	    printf("\n\n\n\n>>> PARABENS!! Voce fez %d pontos! Muito bem!!\n", (jogo + num_jogos)->scores);
        puts("\n\n>>> Pressione < J > para jogar novamente ou < M > para voltar ao menu principal:");
        op = toupper(getchar());
        switch (op)
        { 
            case 'J':
                escolher_nivel(); 
                break;
            case 'M': 
                exibir_menu(); 
                break;
            default: 
                puts("\n >>> Opcao invalida <<<");
                sleep(1);
                break;
        }
    } while(op != 'J' && op !='M');

    num_jogos++;
}

/*-------------------------------------------------------------------
            Mostra a tabela de pontuação dos jogadores 
-------------------------------------------------------------------*/
void exibir_recordes(void)
{
	exibir_cabecalho(1);

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
                    escolher_nivel(); 
                    break;
                case 'M': 
                    exibir_menu(); 
                    break;
                default: 
                    puts("\n >>> Opcao invalida <<<");
                    sleep(1500); 
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
    exibir_menu();
	return;
}

/*-------------------------------------------------------------------
                            Como Jogar 
-------------------------------------------------------------------*/
void exibir_ajuda(void)
{
    exibir_cabecalho(1);
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
    exibir_menu();
}

void limpa_buffer(void)
{
    while(getchar() != '\n');
}