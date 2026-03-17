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

int calc (char *expressao){
    Pilha *ex;
    ex = criar_pilha();
    int res=0, par=0;

    for(int i=0; expressao[i]!='\0'; i++){
        /*if(expressao[i]=='('){
            par++;
        }
        else if(expressao[i]==')'){
            par--;
        }*/
        if(expressao[i]=='/' && par==0){
            empilhar(ex, desempilhar(ex)/desempilhar(ex));
        }
        else if(expressao[i]=='*' && par==0){
            empilhar(ex, desempilhar(ex)*desempilhar(ex));
        }
        else if(expressao[i]=='+' && par==0){
            empilhar(ex, desempilhar(ex)+desempilhar(ex));
        } 
        else if(expressao[i]=='-' && par==0){
            empilhar(ex, desempilhar(ex)+desempilhar(ex));
        }
        else{
            empilhar(ex, expressao[i]);
        }
    }
    res = desempilhar(ex);
    liberar_pilha(ex);
    return res;
}

int main (void){
    char *expressao;
    expressao = malloc(sizeof(char)*100);

    scanf(" %s", expressao);
    printf("%d", calc(expressao));
    
    return 0;
}