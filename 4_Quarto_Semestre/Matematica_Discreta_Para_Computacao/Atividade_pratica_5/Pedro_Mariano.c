#include <stdio.h>
#include <stdbool.h>

#define MAX 5

// Função para verificar se a matriz é reflexiva
bool ehReflexiva(int matriz[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        if (matriz[i][i] != 1)
            return false;
    }
    return true;
}

// Função para verificar se a matriz é antissimétrica
bool ehAntissimetrica(int matriz[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matriz[i][j] == 1 && matriz[j][i] == 1)
                return false;
        }
    }
    return true;
}

// Função para verificar se a matriz é transitiva
bool ehTransitiva(int matriz[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] == 1) {
                for (int k = 0; k < n; k++) {
                    if (matriz[j][k] == 1 && matriz[i][k] != 1)
                        return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int n, opcao;
    do {
        printf("Informe o tamanho da matriz (4 ou 5): ");
        scanf("%d", &n);

        if (n < 4 || n > 5) {
            printf("Tamanho inválido!\n");
            return 1;
        }

        int matriz[MAX][MAX];
        printf("Insira a matriz por linha, cada elemento separado por espaço:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &matriz[i][j]);
            }
        }

        bool reflexiva = ehReflexiva(matriz, n);
        bool antissimetrica = ehAntissimetrica(matriz, n);
        bool transitiva = ehTransitiva(matriz, n);

        if (reflexiva && antissimetrica && transitiva) {
            printf("A relação representada pela matriz é uma relação de ordem parcial.\n");
        } else {
            printf("A relação representada pela matriz não é uma relação de ordem parcial, pois não possui a(s) propriedade(s):\n");
            if (!reflexiva) printf("- Reflexiva\n");
            if (!antissimetrica) printf("- Antissimétrica\n");
            if (!transitiva) printf("- Transitiva\n");
        }

        printf("Digite (1) para informar outra matriz ou (2) para sair: ");
        scanf("%d", &opcao);
    } while (opcao == 1);

    return 0;
}
