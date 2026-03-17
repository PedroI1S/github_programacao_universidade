#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct{
    int i;
    int f;
}Real;

Real* criar(int i, int f){
    Real *r;
    r = malloc(sizeof(Real));
    r->i = i;
    r->f = f;
    return r;
}

Real* soma(Real *r1, Real *r2){
    Real *r3 = criar(r1->i+r2->i, r1->f+r2->f);
}

Real* subtracao(Real *r1, Real *r2){
    Real *r3;
    if(r1->i>r2->i){
        r3 = criar(r1->i-r2->i, r1->f-r2->f);
    }
    else if(r1->i<r2->i){
        r3 = criar(r2->i-r1->i, r2->f-r1->f);
    }
    else{
        if(r1->f>r2->f){
            r3 = criar(r1->i-r2->i, r1->f-r2->f);
        }
        else{
            r3 = criar(r2->i-r1->i, r2->f-r1->f);
        }
    }
    return r3;
}

int arredondar(Real *r){
    if(r->f>=50){
        r->i++;
        r->f=0;
    }else{
        r->f=0;
    }

    return r->i;
}

void imprimir(Real *r){
    while(r->f>=100){
        r->i++;
        r->f-=100;
    }
    while(r->f<0){
        r->i--;
        r->f+=100;
    }
    if(r->f==0){
        printf("%d\n", r->i);
    }else{
        printf("%d,%d\n", r->i, r->f);
    }
}

int main(void){
    Real *r1, *r2;
    int i, f;

    scanf("%d %d", &i, &f);
    r1 = criar(i, f);

    scanf("%d %d", &i, &f);
    r2 = criar(i, f);

    imprimir(r1);
    imprimir(r2);
    imprimir((r1, r2));
    imprimir(subtracao(r1, r2));
    printf("%d\n", arredondar(r1));
    printf("%d\n", arredondar(r2));

    free(r1);
    free(r2);

    return 0;
}