#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct Cell Cell;
typedef struct ListaE ListaE;

struct Cell
{
    int item;
    Cell *next;
};

struct ListaE
{
    Cell *head;
};

static Cell *criar_celula(int key)
{
    Cell *c = (Cell *)malloc(sizeof(Cell));
    c->item = key;
    c->next = NULL;
    return c;
}

ListaE *criar_listaE()
{
    ListaE *l = (ListaE *)malloc(sizeof(ListaE));
    l->head = NULL;
    return l;
}

static int listaE_vazia(ListaE *l)
{
    return (l == NULL) || (l->head == NULL);
}

static int tamanho_LE(ListaE *l)
{
    Cell *aux = l->head;
    int tam = 0;
    while (aux != NULL)
    {
        tam++;
        aux = aux->next;
    }
    return tam;
}

static int procurar(int key, ListaE *l)
{
    Cell *aux = l->head;
    while (aux != NULL)
    {
        if (aux->item == key)
            return 1;
        aux = aux->next;
    }
    return 0;
}

static void imprimir(ListaE *l)
{
    Cell *aux = l->head;
    while (aux != NULL)
    {
        printf("%d", aux->item);
        if (aux->next != NULL)
            printf(", ");
        aux = aux->next;
    }
}

static void imprimir_complemento(ListaE *A, ListaE *U)
{
    Cell *auxU = U->head;
    int aux = 0;
    while (auxU != NULL)
    {
        if (!procurar(auxU->item, A))
        {
            if (aux == 0)
                printf("%d", auxU->item);
            else
                printf(", %d", auxU->item);
            aux = 1;
        }
        auxU = auxU->next;
    }
}

static void imprimir_interseccao(ListaE *A, ListaE *B)
{
    Cell *auxA = A->head;
    int aux = 0;
    while (auxA != NULL)
    {
        if (procurar(auxA->item, B))
        {
            if (aux == 0)
                printf("%d", auxA->item);
            else
                printf(", %d", auxA->item);
            aux = 1;
        }
        auxA = auxA->next;
    }
}

static void imprimir_uniao(ListaE *A, ListaE *B)
{
    Cell *auxA = A->head;
    while (auxA != NULL)
    {
        printf("%d", auxA->item);
        auxA = auxA->next;
        if (auxA != NULL)
            printf(", ");
    }

    Cell *auxB = B->head;
    while (auxB != NULL)
    {
        if (!procurar(auxB->item, A))
        {
            printf(", %d", auxB->item);
        }
        auxB = auxB->next;
    }
}

static void imprimir_conjunto_potencias(ListaE *l)
{
    int tamanho = tamanho_LE(l);
    int total_subsets = pow(2, tamanho);
    if (tamanho == 0)
    {
        printf("{ {} }\n");
        return;
    }

    int *elements = (int *)malloc(tamanho * sizeof(int));
    Cell *aux = l->head;
    int i = 0;
    while (aux != NULL)
    {
        elements[i++] = aux->item;
        aux = aux->next;
    }

    for (int subset = 0; subset < total_subsets; subset++)
    {
        printf("{");
        int first = 1;
        for (int j = 0; j < tamanho; j++)
        {
            if (subset & (1 << j))
            {
                if (!first)
                    printf(", ");
                printf("%d", elements[j]);
                first = 0;
            }
        }
        printf("}");
        if (subset < total_subsets - 1)
            printf(", ");
    }

    free(elements);
}

void imprimir_resultados(ListaE *A, ListaE *A1, ListaE *A2, int escolhaPotencia)
{
    printf("\nA = { ");
    imprimir(A);
    printf(" }\nA1 = { ");
    imprimir(A1);
    printf(" }\nA2 = { ");
    imprimir(A2);
    printf(" }\nP(A%d) = { ", escolhaPotencia);
    if (escolhaPotencia == 1)
        imprimir_conjunto_potencias(A1);
    else
        imprimir_conjunto_potencias(A2);
    printf(" }\nC(A1) = { ");
    imprimir_complemento(A1, A);
    printf(" }\nC(A2) = { ");
    imprimir_complemento(A2, A);
    printf(" }\nU(A1, A2) = { ");
    imprimir_uniao(A1, A2);
    printf(" }\nI(A1, A2) = { ");
    imprimir_interseccao(A1, A2);
    printf(" }\n");
}

void inserir_ultimo(int key, ListaE **l)
{
    if (*l == NULL)
        *l = criar_listaE();

    while (procurar(key, *l))
    {
        printf("Valor %d já está no conjunto. Por favor, insira um valor diferente: ", key);
        scanf("%d", &key);
    }

    if (listaE_vazia(*l))
    {
        Cell *aux = criar_celula(key);
        (*l)->head = aux;
    }
    else
    {
        Cell *aux = (*l)->head;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = criar_celula(key);
    }
}



ListaE *obter_conjunto_aleatorio(ListaE *l, int cardinalidade)
{
    int tamanho = tamanho_LE(l);
    if (tamanho == 0)
    {
        printf("Lista vazia.\n");
        return NULL;
    }

    ListaE *A = criar_listaE();
    int *indices_selecionados = (int *)malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++) {
        indices_selecionados[i] = 0;
    }

    int selecionados = 0;
    while (selecionados < cardinalidade)
    {
        int indice_aleatorio;
        do {
            indice_aleatorio = rand() % tamanho;
        } while (indices_selecionados[indice_aleatorio] == 1);

        indices_selecionados[indice_aleatorio] = 1;

        Cell *aux = l->head;
        for (int i = 0; i < indice_aleatorio; i++)
        {
            aux = aux->next;
        }

        inserir_ultimo(aux->item, &A);
        selecionados++;
    }

    free(indices_selecionados);
    return A;
}

int liberar_LE(ListaE *l)
{
    Cell *aux = NULL;
    while (l->head != NULL)
    {
        aux = l->head;
        l->head = aux->next;
        free(aux);
    }
    free(l);
    return 1;
}
