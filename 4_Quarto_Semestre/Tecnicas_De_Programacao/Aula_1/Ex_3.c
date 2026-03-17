#include <stdio.h>

void formar_matriz(int i, int j) {
    int matriz[i][j];

    for (int x = 0; x < i; x++) {
        for (int y = 0; y < j; y++) {
            if (x == y)
                matriz[x][y] = 0;
            else if (x < y)
                matriz[x][y] = 1;
            else
                matriz[x][y] = -1;

            printf(" %-3d", matriz[x][y]);
        }
        printf("\n");
    }
}

int main(void) {
    int n;
    int i, j;

    do {
        printf("Informe um numero inteiro positivo: ");
        scanf("%d", &n);
    } while (n < 0);

    do {
        printf("Informe as dimensoes da matriz (ixj): ");
        scanf("%d %d", &i, &j);
    } while (i < 0 || j < 0);

    formar_matriz(i, j);

    return 0;
}
