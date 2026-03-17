#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define TAM_MAX 100

typedef struct ItemP ItemP;

typedef struct
{
    int item[TAM_MAX];
    int topo;
} Pilha;

Pilha *criar_pilha()
{
    Pilha *p = malloc(sizeof(Pilha));
    p->item[TAM_MAX] = INT_MAX;
    p->topo = -1;
    return p;
}

int pilha_cheia(Pilha *p)
{
    if (p->topo == INT_MAX - 1)
    {
        return 1;
    }
    return 0;
}

int pilha_vazia(Pilha *p)
{
    if (p->topo == -1)
    {
        return 1;
    }
    return 0;
}

int empilhar(Pilha *p, int chave)
{
    if (pilha_cheia(p) == 0)
    {
        p->topo++;
        p->item[p->topo] = chave;
        return 1;
    }
    return 0;
}

int desempilhar(Pilha *p)
{
    if (pilha_vazia(p) == 0)
    {
        p->topo--;
        return 1;
    }
    return 0;
}

int imprimir_pilha(Pilha *p)
{
    if (pilha_vazia(p) == 0)
    {
        Pilha *aux = p;
        while (pilha_vazia(aux) == 0)
        {
            printf("%d ", aux->item[aux->topo]);
            desempilhar(aux);
        }
        return 1;
    }
    return 0;
}

int converter(Pilha *p, int aux){
    if(pilha_vazia(p)==0){
        for(int i=0; i<aux; i++){
            j =
            p->item[i]=dec_oc(p->item[i]);
        }
    }
    return 0;
}

int dec_oc(int dec){
    int oc=0, i;
    
    for(i=0; dec>8; i++){
        oc+=dec%8*(int)pow(10, i);
        dec=(dec/8);
    }
    oc+=dec*(int)pow(10, i);
    
    return oc;
}

int main (void){
    int aux, chave;
    Pilha *p;
    p = criar_pilha();

    scanf("%d", &aux);

    for(int i=0; i<aux; i++){
        scanf("%d", &chave);
        empilhar(p, chave);
    }

    converter(p, aux);
    imprimir_pilha(p);
    free(p);

    return 0;
}
