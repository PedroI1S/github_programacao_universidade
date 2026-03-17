#include <stdio.h>
#include <stdlib.h>

typedef struct Cell Cell;

typedef struct PilhaE PilhaE;

struct Cell {
    char item;
    Cell *next;
};

struct PilhaE {
    Cell *topo;
};

Cell *criar_celula(char key) {
    Cell *c = (Cell *)malloc(sizeof(Cell));
    c->item = key;
    c->next = NULL;
    return c;
}

PilhaE *criar_pilhaE() {
    PilhaE *p = (PilhaE *)malloc(sizeof(PilhaE));
    p->topo = NULL;
    return p;
}

int pilhaE_vazia(PilhaE *p) {
    return (p == NULL) || (p->topo == NULL);
}

void empilhar(char key, PilhaE *p) {
    Cell *aux;
    if (p == NULL)
        p = criar_pilhaE();
    aux = criar_celula(key);
    aux->next = p->topo;
    p->topo = aux;
}

char desempilhar(PilhaE *p) {
    Cell *aux;
    char item = ' ';
    if (!pilhaE_vazia(p)) {
        aux = p->topo;
        item = aux->item;
        p->topo = aux->next;
        free(aux);
    }
    return item;
}

void imprimir_pilha(PilhaE *p) {
    Cell *aux;
    if (!pilhaE_vazia(p)) {
        aux = p->topo;
        while (aux != NULL) {
            printf("%c\n", aux->item);
            aux = aux->next;
        }
    }
}

int liberar_pilha(PilhaE *p) {
    if (p != NULL) {
        while (!pilhaE_vazia(p))
            desempilhar(p);
        free(p);
        return 1;
    }
    return 0;
}

int ler_empilhar(PilhaE *p) {
    char *aux = calloc(sizeof(char), 255);

    scanf(" %s", aux);
    for (int j = 0; aux[j] != '\0'; j++) {
        if (aux[j] == '(')
            empilhar(aux[j], p);
        else if (aux[j] == ')') {
            if (pilhaE_vazia(p) || desempilhar(p) != '(') {
                free(aux);
                return 0;
            }
        }
    }
    free(aux);
    if (pilhaE_vazia(p))
        return 1;
    else
        return 0;
}

int main(void) {
    int N;
    scanf("%d", &N);
    while (N > 0) {
        PilhaE *p = criar_pilhaE();
        if (ler_empilhar(p) != 0)
            printf("correct\n");
        else
            printf("incorrect\n");
        liberar_pilha(p);
        N--;
    }
    return 0;
}
