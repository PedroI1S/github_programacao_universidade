#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TAM_MAX 100

typedef struct
{
    char item[TAM_MAX];
    int topo;
} Pilha;

Pilha *criar_pilha()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));

    p->topo = -1;

    return p;
}

int pilha_cheia(Pilha *p)
{
    if (p == NULL)
        return -1;
    else if (p->topo == (TAM_MAX - 1))
        return 1;
    else
        return 0;
}

int pilha_vazia(Pilha *p)
{
    if (p == NULL)
        return -1;
    else if (p->topo == -1)
        return 1;
    else
        return 0;
}

int empilhar(Pilha *p, char item)
{
    if (p == NULL)
        p = criar_pilha();

    if (!pilha_cheia(p))
    {
        p->topo++; 

        p->item[p->topo] = item; 

        return 1;
    }

    return 0;
}

char desempilhar(Pilha *p)
{
    char item;

    if (!pilha_vazia(p))
    {
        item = p->item[p->topo];

        p->topo--;
    }

    return item;
}

void imprimir_pilha(Pilha *p)
{
    Pilha aux = *p;
    char item;

    while (!pilha_vazia(&aux))
    {
        item = desempilhar(&aux);

        printf("%c\n", item);
    }
}

void liberar_pilha(Pilha *p)
{
    if (p != NULL)
        free(p);
}

int obter_posicao_topo(Pilha *p)
{
    if (!pilha_vazia(p))
        return p->topo;
    else
        return -1;
}

void ler_empilhar(Pilha *p, int rep)
{
    char *aux;
    aux = malloc(sizeof(char)*100);

    scanf(" %s", aux);
    for (int j = 0; aux[j] != '\0'; j++)
    {
        if (aux[j] == '(' || aux[j] == ')')
        {
            empilhar(p, aux[j]);
        }
    }
    free(aux);
}

int verificar_parentese(Pilha *p)
{
    char aux, abre = 0, fecha = 0;
    while (!pilha_vazia(p))
    {
        aux = desempilhar(p);
        if (aux == '(')
        {
            abre++;
        }
        else
        {
            fecha++;
        }

        if (abre > fecha)
        {
            return 0;
        }
    }
    if (fecha == abre)
    {
        return 1;
    }
    
    return 0;
}

int main(void)
{
    int aux;
    Pilha *p;
    p = criar_pilha();

    scanf("%d", &aux);
    int test[aux];

    for(int i=0; i<aux; i++){
        ler_empilhar(p, aux);
        test[i] = verificar_parentese(p);
    }

    for(int i=0; i<aux; i++){
        if(test[i]!=0){
            printf("correct \n");
        }
        else{
            printf("incorrect\n");
        } 
    }
    
    free(p);
    
    return 0;
}