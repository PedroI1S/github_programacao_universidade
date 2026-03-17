#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define MAX_SIZE 100

list* create(){
    list *l = (list*)(malloc(sizeof(list)));
    l->qtd = -0;

    return l;
}

int empty(list *l){
    if(l==NULL || l->qtd==0){
        return 0;
    }
    return 1;
}

int full(list *l){
    if(l->qtd==MAX_SIZE){
        return 0;
    }
    return 1;
}

int insert(list *l, int key){
    if(full(l)!=0){
        l->item[l->qtd]=key;
        l->qtd++;

        return 1;
    }
    return 0;
}

int buscar(list *l, int key){
    int i=-1;

    if(empty(l)!= 0){
        do{
            i++;
        }while(l->item[i]!=key);
        return i;
    }
    return -1;
}

int remover(list *l, int key){
    int i;

    if(empty(l)!=0){
        for(i=buscar(l, key); i<(l->qtd)-1; i++){
            l->item[i] = l->item[i+1];
            l->qtd--;
        }
        return 1;
    }
     return 0;
}

int imprint(list *l){
    if(empty(l)!=0){
        for(int i=0; i<l->qtd; i++){
            printf("%d ", l->item[i]);
         }
        return 1;
    }
    return 0;
}

int invert(list *l){
    if(empty(l)!=0){
        int aux =0;
        for(int i=(l->qtd - 1), j=0; i>=j; i--, j++){
           aux = l->item[i];
           l->item[i] = l->item[j];
           l->item[j] = aux;
       }
        return 1;
    }
    return 0;
}
