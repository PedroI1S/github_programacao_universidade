#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TAM_MAX 100

typedef struct Fila Fila;

struct Fila {
    int item[TAM_MAX];
    int ini;
    int fim;
    int tam;
};

Fila *criar_fila() {
    Fila *f = (Fila *)malloc(sizeof(Fila));

    f->ini = -1;
    f->fim = -1;
    f->tam = 0;

    return f;
}

int fila_cheia(Fila *f) {
    if (f == NULL)
        return -1;
    else if (f->tam < TAM_MAX)
        return 0;
    else
        return 1;
}

int fila_vazia(Fila *f) {
    if (f == NULL)
        return -1;
    else if (f->tam > 0)
        return 0;
    else
        return 1;
}

int enfileirar(Fila *f, int chave) {
    if (f == NULL)
        f = criar_fila();

    if (!fila_cheia(f)) {
        if (f->ini < 0)
            f->ini = 0;

        if (f->fim < TAM_MAX - 1)
            f->fim++;
        else
            f->fim = 0;

        f->item[f->fim] = chave;

        f->tam++;

        return 1;
    }

    return 0;
}

int desenfileirar(Fila *f) {
    int item = INT_MIN;

    if (!fila_vazia(f)) {
        item = f->item[f->ini];

        if (f->ini < TAM_MAX - 1)
            f->ini++;
        else
            f->ini = 0;

        f->tam--;

        if (f->tam == 0) {
            f->ini = -1;
            f->fim = -1;
        }
    }

    return item;
}

Fila *gerenciar_transito(Fila *E1, Fila *E2, Fila *E3) {
    Fila *R = criar_fila();

    while (!fila_vazia(E1) || !fila_vazia(E2) || !fila_vazia(E3)) {
        for(int i=0; i<3 && !fila_vazia(E1); i++){
            enfileirar(R, desenfileirar(E1));
        }
        for(int i=0; i<3 && !fila_vazia(E2); i++){
            enfileirar(R, desenfileirar(E2));
        }
        for(int i=0; i<3 && !fila_vazia(E3); i++){
            enfileirar(R, desenfileirar(E3));
        }
    }

    return R;
}

void Ler_estrada(Fila *E1, Fila *E2, Fila *E3) {
    int elemento;

    while (1) {
        scanf("%d", &elemento);
        if (elemento == -1)
            break;
        enfileirar(E1, elemento);
    }

    while (1) {
        scanf("%d", &elemento);
        if (elemento == -1)
            break;
        enfileirar(E2, elemento);
    }

    while (1) {
        scanf("%d", &elemento);
        if (elemento == -1)
            break;
        enfileirar(E3, elemento);
    }
}

int main() {
    Fila *E1 = criar_fila(), *E2 = criar_fila(), *E3 = criar_fila(), *R;

    Ler_estrada(E1, E2, E3);

    R = gerenciar_transito(E1, E2, E3);

    while (!fila_vazia(R)) {
        printf("%d ", desenfileirar(R));
    }

    return 0;
}
