#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int num, maior = 0, menor = 0, first = 1;

    do {
        printf("Informe um número (0 para encerrar): ");
        scanf("%d", &num);

        if (num != 0) {
            if (first) {
                maior = num;
                menor = num;
                first = 0;
            } else {
                if (num > maior) {
                    maior = num;
                }
                if (num < menor) {
                    menor = num;
                }
            }
        }
    } while (num != 0);

    printf("\nO maior valor informado foi: %d", maior);
    printf("\nO menor valor informado foi: %d", menor);

    return 0;
}
