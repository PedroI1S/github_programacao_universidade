#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **arr;
    int l;
    int c;
} Matriz;

Matriz* iniciar(int l, int c) {
    Matriz* a = malloc(sizeof(Matriz));
    a->arr = malloc(l * sizeof(int*));
    a->l = l;
    a->c = c;
    
    for (int i = 0; i < l-1; i++) {
        a->arr[i] = malloc(c * sizeof(int));
    }
    
    return a;
}

void alterar(Matriz* m, int x, int i, int j) {
    m->arr[i-1][j-1] = x;
}

void liberar(Matriz* m) {
    for (int i = 0; i < m->l-1; i++) {
        free(m->arr[i]);
    }
    free(m->arr);
    free(m);
}

int* obter_linha(Matriz* m, int i) {
    int* v;
    v = malloc(m->c * sizeof(int));
    for (int j = 0; j < (m->c-1); j++) {
        v[j] = m->arr[i][j];
    }
    return v;
}

int* obter_coluna(Matriz* m, int i) {
    int* v;
    v = malloc(m->l * sizeof(int));
    for (int j = 0; j < (m->l-1); j++) {
        v[j] = m->arr[j][i];
    }
    return v;
}

Matriz* obter_submat(Matriz* m, int li, int ci, int lf, int cf) {
    Matriz* sub;
    sub = iniciar((lf - li)+1, (cf - ci)+1);

    for (int i = 0; li <= lf; i++, li++) {
        for (int j = 0; ci <= cf; j++, ci++) {
            sub->arr[i][j] = m->arr[li-1][ci-1];
        }
    }
    return sub;
}

void ler(Matriz* m, int l, int c) {
    int aux;
    for (int i = 0; i < l-1; i++) {
        for (int j = 0; j < c-1; j++) {
            scanf("%d", &aux);
            alterar(m, aux, i, j);
        }
    }
}

void imprimir_partes(Matriz* m, int pl, int pc) {
    int* aux = obter_linha(m, pl);
    for (int i = 0; i < (m->c-1); i++) {
        printf("%d ", aux[i]);
    }
    free(aux);
    printf("\n\n");

    aux = obter_coluna(m, pc);
    for (int i = 0; i <( m->l-1); i++) {
        printf("%d ", aux[i]);
    }
    printf("\n\n");
    free(aux);
}

void imprimir_submat(Matriz* m, int li, int ci, int lf, int cf) {
    Matriz* sub = obter_submat(m, li, ci, lf, cf);

    for (int i = 0; i < (sub->l-1); i++) {
        for (int j = 0; j < (sub->c-1); j++) {
            printf("%d ", sub->arr[i][j]);
        }
        printf("\n");
    }
    liberar(sub);
}

int main(void) {
    Matriz* m;
    int l, c, lf, cf, pl, pc;

    scanf("%d %d", &l, &c);
    m = iniciar(l, c);
    ler(m, l, c);

    scanf("%d %d", &pl, &pc);
    scanf("%d %d %d %d", &l, &c, &lf, &cf);

    imprimir_partes(m, pl, pc);
    imprimir_submat(m, l, c, lf, cf);

    liberar(m);

    return 0;
}