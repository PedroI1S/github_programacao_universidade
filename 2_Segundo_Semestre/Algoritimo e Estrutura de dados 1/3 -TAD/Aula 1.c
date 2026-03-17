#include<stdio.h>
#include<stdlib.h>
#define MAX_VALUE 100

typedef struct{
    int *item;
    int q;
    int n;
}Vetor;

Vetor * iniciar(int n){
    Vetor *v;

    v = malloc(sizeof(Vetor));
    v->n = n;
    v->item = malloc(sizeof(int)*n);
    v->q = 0;

    return v;
}

int inserir(Vetor *v, int x){
    if(v->item[v->q] = x){
        v->q++;
        return 1;
    }
    return 0;
}

Vetor * intercalar(Vetor *v1, Vetor *v2){
    Vetor *v3;
    v3 = iniciar(v1->q + v2->q);

    for(int i = 0; i<v1->q && i<v2->q; i++){
        if(i<v1->q){
            v3->item[v3->q] = v1->item[i];
            v3->q++;
        }
        if(i<v2->q){
            v3->item[v3->q] = v2->item[i];
            v3->q++;
        }
    }
    return v3;
}

Vetor * concatenar(Vetor *v1, Vetor *v2){
    Vetor *v3;
    v3 = iniciar(v1->q + v2->q);

    for(int i = 0; i<(v1->q + v2->q); i++){
        if(i<v1->q){
            v3->item[v3->q] = v1->item[i];
            v3->q++;
        }else{
            v3->item[v3->q] = v2->item[i-v1->q];
            v3->q++;
        }
    }
    return v3;
}

Vetor * subvetor(Vetor *v1, int ini, int fim){
    Vetor *v2;
    v2 = iniciar(fim-ini+1);

    for(int i=ini; i<(fim); i++){
        v2->item[v2->q]=v1->item[i];
        v2->q++;
    }
    return v2;
}

void imprimir (Vetor *v){
    for(int i=0; i<v->q; i++){
        printf("%d ", v->item[i]);
    }
    printf("\n");
}

void libertar (Vetor *v){
    free(v->item);
    free(v);
}

int main (void){
    int t, aux, ini, fim;
    Vetor *v1, *v2, *v3;

    scanf("%d", &t);
    v1 = iniciar(t);

    for(int i=0; i<t; i++){
        scanf("%d", &aux);
        inserir(v1, aux);
    }

    scanf("%d", &t);
    v2 = iniciar(t);

    for(int i=0; i<t; i++){
        scanf("%d", &aux);
        inserir(v2, aux);
    }

    scanf("%d %d", &ini, &fim);
    
    v3 = intercalar(v1, v2);
    imprimir(v3);
    libertar(v3);

    v3 = concatenar(v1, v2);
    imprimir(v3);
    libertar(v3);

    v3 = subvetor(v1, ini, fim);
    imprimir(v3);

    libertar(v1);
    libertar(v2);
    libertar(v3);

    return 0;
}