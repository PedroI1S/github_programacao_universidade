#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
    char nomes[MAX_SIZE][MAX_SIZE];
    int tamanho;
} Lista;

Lista *criar_lista()
{
    Lista *l = malloc(sizeof(Lista));
    l->tamanho = 0;

    return l;
}

void inserir(Lista *lista, char nome[MAX_SIZE])
{
    if (lista->tamanho < MAX_SIZE)
    {
        strcpy(lista->nomes[lista->tamanho], nome);
        lista->tamanho++;
    }
}

void imprimir(Lista *lista, char string_procurada[MAX_SIZE])
{
    for (int i = 0; i < lista->tamanho; i++)
    {
        if (strstr(lista->nomes[i], string_procurada) != NULL)
        {
            printf("%s\n", lista->nomes[i]);
        }
    }
}

void liberar_pilha(Pilha *p)
{
    if (p != NULL)
        free(p);
}

int main()
{
    char string_procurada[MAX_SIZE];
    int num_contatos;

    scanf("%s", string_procurada);

    scanf("%d", &num_contatos);

    Lista *l;
    l = criar_lista();

    for (int i = 0; i < num_contatos; i++)
    {
        char nome[MAX_SIZE];
        scanf("%s", nome);
        inserir(l, nome);
    }

    imprimir(l, string_procurada);

    return 0;
}
