#include "threading.h"
#include "anagrame.h"
#include <pthread.h>

int validar_palavra_existente(char* palavra)
{
    pthread_t threads[num_threads];
    _ARGS *args = malloc (num_threads * sizeof(_ARGS));

    for (int i = 0; i < num_threads; i++)
    {
        (args + i)->tid = i;
        (args + i)->palavra = palavra;

        if ( pthread_create(&threads[i], NULL, busca_palavra, (void*) (args + i)))
        {
            puts("Falha ao criar thread!! Encerrando o jogo.");
            exit(1);
        }
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
        free(threads + i);
        free(args + i);
    }

    if ( achou )
    {
        achou = 0;
        return 0;
    }
    else return 5;
}

void* busca_palavra (void* args)
{
    int tid = ((_ARGS*) args)->tid;
    char* palavra = ((_ARGS*) args)->palavra;

    for (int i = tid; i < TAM_DIC; i += num_threads)
    {
        if (achou == 0)
        {
            if (strcmp(dicionario[i], palavra) == 0)
            {
                achou++;
                break;
            }
        }
        else break;
    }
    
    free(palavra);
    pthread_exit(NULL);
}