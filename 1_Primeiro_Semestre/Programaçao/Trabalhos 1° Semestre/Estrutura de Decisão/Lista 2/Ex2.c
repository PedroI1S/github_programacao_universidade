#include <stdio.h>
#include <stdlib.h>

int main()
{
    int valor, nota200, nota100, nota50, nota20, nota10, nota5, nota2;
    printf("Digite o valor do saque: ");
    scanf("%d", &valor);
    if(valor >= 10 && valor <= 600)
    {
        nota200 = valor / 200;
        valor = valor % 200;
        nota100 = valor / 100;
        valor = valor % 100;
        nota50 = valor / 50;
        valor = valor % 50;
        nota20 = valor / 20;
        valor = valor % 20;
        nota10 = valor / 10;
        valor = valor % 10;
        nota5 = valor / 5;
        valor = valor % 5;
        nota2 = valor / 2;
        printf("Notas de R$200: %d\n", nota200);
        printf("Notas de R$100: %d\n", nota100);
        printf("Notas de R$50: %d\n", nota50);
        printf("Notas de R$20: %d\n", nota20);
        printf("Notas de R$10: %d\n", nota10);
        printf("Notas de R$5: %d\n", nota5);
        printf("Notas de R$2: %d\n", nota2);
    }
    else
    {
        printf("Valor inválido.\n");
    }
    return 0;
}
