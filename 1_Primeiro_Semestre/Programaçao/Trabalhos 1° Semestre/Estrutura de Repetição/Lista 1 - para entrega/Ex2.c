/*Uma empresa deseja calcular a depreciação de seus bens. Para tanto, desenvolver um programa que
obtenha a taxa de depreciação anual para os bens, o valor do bem a ser depreciado e o período em anos.
Valor depreciado = valor do bem * (taxa de depreciação / 100)
Valor do bem depreciado = valor do bem – valor depreciado
Considere que a taxa de depreciação tem valor fixo de 1.5.*/
#include<stdio.h>

int main (void)
{
    float valor, soma;
    int ano, i=1;

    do
    {
        printf("Informe o valor do bem a ser depreciado: ");
        scanf("%f", &valor);
    }while(valor<=0);
    do
    {
        printf("Periodo(em anos): ");
        scanf("%d", &ano);
    }while(ano<=0);

    printf("\nAno\t\tValor do bem\tDepreciacao\tValor depreciado\n");
    printf("===========================================================\n");

    while(ano>=i)
    {
        printf("%-2d \t\tR$%.2f\t%.2f", i, valor, 0.015*valor);
        soma+=valor*0.015;
        valor=valor-0.015*valor;
        printf("\t\t%.2f\n", valor);
        i++;
    }
    printf("===========================================================\n");

    printf("Depreciacao acumulada: %.2f\n", soma);

    return 0;
}
