#include <stdio.h>

double calcular_e(int n) {
    double e = 1.0;
    double termo = 1.0;

    for (int i = 1; i < n; i++) {
        termo /= i;
        e += termo;
    }

    return e;
}

int main() {
    int n;
    printf("Digite o numero de termos (n) para calcular e: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Numero de termos deve ser maior que zero.\n");
        return 1;
    }

    double e = calcular_e(n);
    printf("O valor aproximado de e com %d termos e: %lf\n", n, e);

    return 0;
}
