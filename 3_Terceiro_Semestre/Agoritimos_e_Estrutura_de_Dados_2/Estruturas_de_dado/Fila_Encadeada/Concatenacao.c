#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

//FILA TAD

typedef struct Cell Cell;
typedef struct FilaE FilaE;

struct Cell{
    int item;
    Cell *next;
};


struct FilaE{
    Cell *inicio;
    Cell *fim;
};


Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->item = key;

    c->next = NULL;

    return c;
}


FilaE* criar_filaE(){
    FilaE *f = (FilaE*) malloc(sizeof(FilaE));
    
    f->inicio = NULL;
    f->fim = NULL;
    
    return f;
}


int filaE_vazia(FilaE* f){
    return (f == NULL) || (f->inicio == NULL);
}


void enfileirar(int key, FilaE* f){
    Cell *aux;

    if (f == NULL)
        f = criar_filaE();

    aux = criar_celula(key);

    if (f->inicio == NULL)
        f->inicio = f->fim = aux;
    else{
        f->fim->next = aux;
        f->fim = f->fim->next;
    }

}


int desenfileirar(FilaE* f){
    Cell *aux;
    int item = INT_MIN;

    if (!filaE_vazia(f)){
        aux = f->inicio;

        f->inicio = aux->next;
        
        item = aux->item;

        free(aux);
    }

    return item;
}


void imprimir_fila(FilaE* f){
    Cell *aux;

    if (!filaE_vazia(f)){
        aux = f->inicio;

        while (aux != NULL){
            printf("%d ", aux->item);
            aux = aux->next;
        }
        
        printf("\n");
    }
}


int liberar_filaE(FilaE* f){
    if (!filaE_vazia(f)){
        while (f->inicio != NULL)
            desenfileirar(f);

        free(f);

        return 1;
    }

    return 0;
}

//Pilha TAD

typedef struct PilhaE PilhaE;

struct PilhaE{
    Cell *topo;
};

PilhaE* criar_pilhaE(){
    PilhaE* p = (PilhaE*) malloc(sizeof(PilhaE));

    p->topo = NULL;

    return p;
}


int pilhaE_vazia(PilhaE *p){
    return (p == NULL) || (p->topo == NULL);
}


void empilhar(int key, PilhaE *p){
    Cell *aux;

    if (p == NULL)
        p = criar_pilhaE();

    aux = criar_celula(key);

    aux->next = p->topo;

    p->topo = aux;
}


int desempilhar(PilhaE *p){
    Cell *aux;
    int item = ' ';

    if (!pilhaE_vazia(p)){
        aux = p->topo;
        
        item = aux->item;

        p->topo = aux->next;

        free(aux);
    }

    return item;
}

int liberar_pilha(PilhaE *p){
    if (p != NULL){
        while (!pilhaE_vazia(p))
            desempilhar(p);

        free(p);

        return 1;
    }

    return 0;
}

//FUNCAO CRIADA

FilaE* concatenacao(FilaE *f1, FilaE *f2){
    FilaE *f3 = criar_filaE();
    PilhaE *Paux = criar_pilhaE();
    
    while(!filaE_vazia(f2))
        empilhar(desenfileirar(f2), Paux);
    
    while(!filaE_vazia(f1))
        empilhar(desenfileirar(f1), Paux);


    while(!pilhaE_vazia(Paux))
        enfileirar(desempilhar(Paux), f3);

    liberar_pilha(Paux);
    return f3;
}

//MAIN

int main() {
    FilaE *f1 = criar_filaE(), *f2 = criar_filaE(), *f3;
    int aux=0;
    
    while(1){
        scanf("%d", &aux);
        if(aux == -1)
            break;
        enfileirar(aux, f1);
    }
    while(1){
        scanf("%d", &aux);
        if(aux == -1)
            break;
        enfileirar(aux, f2);
    }

    f3 = concatenacao(f1, f2);
    liberar_filaE(f1);
    liberar_filaE(f2);
    
    imprimir_fila(f3);
    liberar_filaE(f3);

    return 0;
}
