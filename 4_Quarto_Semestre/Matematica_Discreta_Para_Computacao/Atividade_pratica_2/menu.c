#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mmc(int a, int b) {
    return (a * b) / mdc(a, b);
}

void fat_primos (int n){
    for (int i = 2; n > 1; i++) {
        while (n % i == 0) {
            n /= i;
            printf("%d", i);
            if (n > 1) {
                printf(".");
            }
        }
    }
}

int quociente (int n1, int n2){
    int quociente = -1;

    if(n2 != 0)
        quociente = n1/n2;

    return quociente;
}

int resto (int n1, int n2){
    int resto = -1;

    if(n2 != 0)
        resto = n1%n2;

    return resto;
}

int main() {
    int opcao;

    do {
        int n1, n2;

        printf("Informe os números dividendo e divisor separados por vírgula: ");
        scanf("%d, %d", &n1, &n2);

        printf("q = %d ; r = %d\n", quociente(n1, n2), resto(n1, n2));
        printf("%d = ", n1);
        fat_primos(n1);
        printf("\n%d = ", n2);
        fat_primos(n2);
        printf("\n");

        int mdc_result = mdc(n1, n2);
        int mmc_result = mmc(n1, n2);
        printf("mdc(%d,%d) = %d\n", n1, n2, mdc_result);
        printf("mmc(%d,%d) = ", n1, n2);
        fat_primos(mmc_result);
        printf("\n");


        printf("\nDigite (1) para informar outro par de números ou digite (2) para sair: ");
        scanf("%d", &opcao);
    } while (opcao == 1);

    return 0;
}
