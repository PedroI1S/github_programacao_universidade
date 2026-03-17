#include <stdio.h>

int main (void)
{
    int num, d1, d2, d3, numr;

    printf("Informe um numero inteiro com ate tres digitos: ");
    scanf("%d", &num);

    d1 = num / 100;
    d2 = (num % 100)/10;
    d3 = num % 10;
    numr = (d3*100) + (d2*10) + d1;

    printf("\n%d eh o primeiro digito", d1);
    printf("\n%d eh o segundo digito", d2);
    printf("\n%d eh o terceiro digito", d3);
    printf("\n\nO inverso do numero eh: %d", numr);

    return 0;
}
