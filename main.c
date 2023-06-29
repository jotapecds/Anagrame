#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "anagrame.c"

/*
** Módulo main.c
**
** Fonte principal do jogo Anagra-me
*/

int main(int argc, char *argv[])
{
	if(inicializar() == 0)
		argc > 1 ? 
			processar(atoi(argv[1])) : 
			processar(0);
		
	terminar();	
	return 0;
}