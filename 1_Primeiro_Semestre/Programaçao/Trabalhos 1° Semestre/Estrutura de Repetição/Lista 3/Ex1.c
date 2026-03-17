#include <stdio.h>

int main() {
    int num, i, j, primo;

    do {
        printf("Digite um numero positivo: ");
        scanf("%d", &num);
    } while (num <= 0);

    printf("Os primeiros %d numeros primos sao:\n", num);

    for (i = 2; num > 0; i++) {
        primo = 1;

        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                primo = 0;
                break;
            }
        }

        if (primo) {
            printf("%d ", i);
            num--;
        }
    }

    return 0;
}
