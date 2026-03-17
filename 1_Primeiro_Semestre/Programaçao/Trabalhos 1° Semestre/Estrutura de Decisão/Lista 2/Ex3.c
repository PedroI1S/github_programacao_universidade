#include <stdio.h>

int MAIN (void)
{
    int numero, digito1, digito2, digito3, digito4, digito5, soma, inverso;
    printf("Digite um número de cinco dígitos: ");
    scanf("%d", &numero);
    if(numero >= 10000 && numero <= 99999)
    {
        digito1 = numero / 10000;
        numero = numero % 10000;
        digito2 = numero / 1000;
        numero = numero % 1000;
        digito3 = numero / 100;
        numero = numero % 100;
        digito4 = numero / 10;
        digito5 = numero % 10;
        soma = digito1 + digito2 + digito3 + digito4 + digito5;
        inverso = digito5 * 10000 + digito4 * 1000 + digito3 * 100 + digito2 * 10 + digito1;
        printf("Primeiro dígito: %d\n", digito1);
        printf("Segundo dígito: %d\n", digito2);
        printf("Terceiro dígito: %d\n", digito3);
        printf("Quarto dígito: %d\n", digito4);
        printf("Quinto dígito: %d\n", digito5);
        printf("Soma dos dígitos: %d ", soma);
        if(soma % 2 == 0)
        {
            printf("(par)\n");
        }
        else
        {
            printf("(ímpar)\n");
        }
        printf("Inverso do número: %d ", inverso);
        if(inverso % 5 == 0)
        {
            printf("(é múltiplo de 5)\n");
        }
        else
        {
            printf("(não é múltiplo de 5)\n");
        }
    }
    else
    {
        printf("Número inválido.\n");
    }
    return 0;
}
