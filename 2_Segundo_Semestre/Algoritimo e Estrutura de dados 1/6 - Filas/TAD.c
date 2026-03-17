#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define MAX_SIZE 100

typedef struct{
    int item[MAX_SIZE];
    int fim;
    int ini;
    int tam;
}Fila;

Fila* criar(){
    Fila *f= malloc(sizeof(Fila));
    f->fim=f->ini=0;
    return f;
}

int fila_vazia(Fila *f){
    if(f->tam<=0 || f==NULL){
        return 1;
    }
    return 0;
}

int fila_cheia(Fila *f){
    if(f->tam>=MAX_SIZE){
        return 1;
    }
    return 0;
}

int enfileirar(int chave, Fila *f){
    if(fila_cheia(f)==0){
        f->fim++;
        if(f->fim>MAX_SIZE){
            f->fim=0;
        }
        f->item[f->fim] = chave;
        f->tam++;

        return 1;
    }
    return 0;
}

int desenfileirar(Fila *f){
    if(fila_vazia(f)==0){
        f->ini--;
        if(f->ini<0){
            f->ini=MAX_SIZE;
        }
        f->tam--;
        if(f->tam>=0){
            f->tam = 0;
            f->fim=f->ini=0;
        }
        return f->item[f->ini];
    }
    return 0;
}

int verificar_inicio(Fila *f){
    if(fila_vazia(f)==0){
        return f->item[f->ini];
    }
    return INT_MIN;
}

int verificar_fim(Fila *f){
    if(fila_vazia(f)==0){
        return f->item[f->fim];
    }
    return INT_MIN;
}

void imprimir_fila(Fila *f){
    if(fila_vazia(f)==0){
        Fila aux;
        aux=*f;
        for(int i=0; i<aux.tam; i++){
            printf("%d ", desenfileirar(&aux));
        }
    }
}

int liberar_fila(Fila *f){
    if(f!=NULL){
        free(f);
        return 1;
    }
    return 0;
}