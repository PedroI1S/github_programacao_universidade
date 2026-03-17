#include <stdio.h>

int main (void)
{
    int num, dig1, dig2, dig3, dig4, dig5;
    printf("informe um numero com ate 5 caracteres: ");
    scanf("%d", &num);

    dig5 = num / 10000;
    dig4 = (num % 10000)/1000;
    dig3 = (num % 1000)/100;
    dig2 = (num % 100)/10;
    dig1 = num % 10;

    printf("\n\n%d eh o primeiro numero", dig5);
    printf("\n%d eh o segundo numero", dig4);
    printf("\n%d eh o terceiro numero", dig3);
    printf("\n%d eh o quarto numero", dig2);
    printf("\n%d eh o quinto numero", dig1);

    return 0;
}
