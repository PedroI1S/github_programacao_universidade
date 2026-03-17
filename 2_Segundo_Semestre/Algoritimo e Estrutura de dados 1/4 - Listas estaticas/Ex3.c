#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct{
    int item[MAX_SIZE];
    int tam;
}Lista;

Lista* criar_lista(){
    Lista *l = (Lista*) malloc(sizeof(Lista));

    l->tam = 0;

    return l;
}

int lista_vazia(Lista *l){
    return (l == NULL) || (l->tam == 0);
}

int lista_cheia(Lista *l){
    return (l != NULL) && (l->tam == MAX_SIZE);
}

int buscar(Lista *l, int chave){
    int i;

    if (!lista_vazia(l)){
        for (i = 0; i < l->tam; i++)
            if (l->item[i] == chave)
                return i;
    }

    return -1;
}

int inserir(Lista *l, int chave){
    if (l == NULL)
        l = criar_lista();

    if (!lista_cheia(l)){
        l->item[l->tam] = chave;

        l->tam++;

        return 1;
    }

    return 0;
}

int remover(Lista *l, int chave){
    int i, p = buscar(l, chave);

    if (p > -1){
        for (i = p; i < l->tam - 1; i++)
            l->item[i] = l->item[i + 1];

        l->tam--;

        return 1;
    }

    return 0;
}

void imprimir_lista(Lista *l){
    int i;

    if (!lista_vazia(l)){
        for (i = 0; i < l->tam; i++)
            printf("%d ", l->item[i]);

        printf("\n");
    }
}

int liberar_lista(Lista *l){
    if (l != NULL){
        free(l);

        return 1;
    }

    return 0;
}

Lista* concatenar(Lista *l1, Lista *l2){
    Lista *l3 = NULL;
    int i;

    if (l1 == NULL)
        l3 = l2;
    else if (l2 == NULL)
        l3 = l1;
    else if (l1->tam + l2->tam <= MAX_SIZE){
        l3 = criar_lista();

        for (i = 0; i <  l1->tam; i++)
            inserir(l3, l1->item[i]);

        for (i = 0; i <  l2->tam; i++)
            inserir(l3, l2->item[i]);
    }

    return l3;
}

int inserir_ordenado(Lista *l, int chave){
    int i;

    if (l == NULL)
        l = criar_lista();

    if (!lista_cheia(l)){
        l->tam++;

        for (i = l->tam - 1; (i > 0) && (chave < l->item[i - 1]); i--)
            l->item[i] = l->item[i - 1];

        l->item[i] = chave;

        return  1;
    }

    return 0;
}

void pares_impares(Lista *l){
    Lista *p = criar_lista(), *i=criar_lista();
    int aux;
    
    for(int j=0; j<l->tam; j++){
        if(l->item[j]%2!=0){
            inserir_ordenado(i, l->item[j]);
        }
        else{
            inserir_ordenado(p, l->item[j]);
        }
    }

    l=concatenar(p,i);
    liberar_lista(p);
    liberar_lista(i);
}
        
void ler(Lista *l){
    int key=0;

    while (key!= -1)
    {
        scanf("%d", &key);
        if(key!=-1){
            inserir(l, key);
        }
    }
}

int main (void){
    Lista *l = criar_lista();

    ler(l);
    pares_impares(l);

    imprimir_lista(l);

    liberar_lista(l);

    return 0;
}