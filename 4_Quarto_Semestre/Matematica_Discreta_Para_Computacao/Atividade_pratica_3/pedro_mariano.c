#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fatorial(int n) {
    if (n <= 1) return 1;
    return n * fatorial(n - 1);
}

void permutacoes(int *arr, int n, int tamanho, int *usados, int *resultado, int nivel) {
    if (nivel == tamanho) {
        for (int i = 0; i < tamanho; i++) {
            printf("%d", resultado[i]);
        }
        printf(" ");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!usados[i]) {
            usados[i] = 1;
            resultado[nivel] = arr[i];
            permutacoes(arr, n, tamanho, usados, resultado, nivel + 1);
            usados[i] = 0;
        }
    }
}

void combinacoes(int *arr, int n, int tamanho, int *resultado, int nivel, int inicio) {
    if (nivel == tamanho) {
        for (int i = 0; i < tamanho; i++) {
            printf("%d", resultado[i]);
        }
        printf(" ");
        return;
    }

    for (int i = inicio; i < n; i++) {
        resultado[nivel] = arr[i];
        combinacoes(arr, n, tamanho, resultado, nivel + 1, i + 1);
    }
}

void combinacoes_repeticao(int *arr, int n, int tamanho, int *resultado, int nivel, int inicio, int *count) {
    if (nivel == tamanho) {
        if (*count < 4) { // Mostra apenas 4 combinações
            for (int i = 0; i < tamanho; i++) {
                printf("%d", resultado[i]);
            }
            printf(" ");
            (*count)++;
        }
        return;
    }

    for (int i = inicio; i < n; i++) {
        resultado[nivel] = arr[i];
        combinacoes_repeticao(arr, n, tamanho, resultado, nivel + 1, i, count);
    }
}

int main() {
    int n, m, q;
    do {
        printf("Informe os valores de n, m, q separados por vírgula (ex: 3,2,4): ");
        scanf("%d,%d,%d", &n, &m, &q);

        if (!(m < n && q > n && (n == 3 || n == 4) && (q == 4 || q == 5 || q == 6))) {
            printf("Valores inválidos. Certifique-se de que m < n, q > n, e que n e q estão dentro dos valores permitidos.\n");
            continue;
        }

        int elementos[n];
        for (int i = 0; i < n; i++) {
            printf("Informe o %d° elemento: ", i+1);
            scanf("%d", &elementos[i]);
        }

        printf("\n(a) Permutações de tamanho %d:\n", n);
        int usados[n];
        int resultado[n];
        memset(usados, 0, sizeof(usados));
        permutacoes(elementos, n, n, usados, resultado, 0);
        printf("\nTotal = %d\n", fatorial(n));

        printf("\n(b) Permutações de %d elementos:\n", m);
        memset(usados, 0, sizeof(usados));
        permutacoes(elementos, n, m, usados, resultado, 0);
        printf("\nTotal = %d\n", fatorial(n) / fatorial(n - m));

        printf("\n(c) Combinações de %d elementos:\n", m);
        int resultado_combinacoes[m];
        combinacoes(elementos, n, m, resultado_combinacoes, 0, 0);
        printf("\nTotal = %d\n", fatorial(n) / (fatorial(m) * fatorial(n - m)));

        printf("\n(d) Combinações com repetição de %d elementos:\n", q);
        int resultado_repeticoes[q];
        int count = 0;
        combinacoes_repeticao(elementos, n, q, resultado_repeticoes, 0, 0, &count);
        printf("\nTotal = %d\n", fatorial(q + n - 1) / (fatorial(q) * fatorial(n - 1)));

        int opcao;
        printf("\nDigite (1) para informar outro conjunto de números ou (2) para sair: ");
        scanf("%d", &opcao);
        if (opcao == 2) break;

    } while (1);

    return 0;
}
