#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct CellP{
    int key;
    CellP *next;
};

struct PilhaE{
    CellP *topo;
};

CellP *criar_celulaP(int key){
    CellP* c = malloc(sizeof(CellP));

    c->key = key;
    c->next = NULL;

    return c;
}

PilhaE *criar_pilha(){
    PilhaE* p = malloc(sizeof(PilhaE));

    p->topo = NULL;

    return p;
}

int pilha_vazia(PilhaE *p){
    return(p == NULL || p->topo == NULL);
}

void empilhar(int key, PilhaE *p){
    CellP* c = criar_celulaP(key);

    if(p==NULL)
        p = criar_celulaP(NULL);

    c->next = p->topo;
    p->topo = c;
}

void desempilhar(PilhaE *p){
    int t = INT_MIN;
    CellP *aux = criar_celulaP(NULL);

    if(!pilha_vazia(p)){
        aux = p->topo;
        p->topo = aux->next;
        t = aux->key;
        free(aux);
    }
    return t;
}

int valor_topo(PilhaE *p){
    int t = INT_MIN;

    if(!pilha_vazia(p))
        return p->topo;
    else
        return t;
}