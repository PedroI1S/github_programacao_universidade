#include<stdio.h>

int main (void)
{
    float i, j=15, num;

    printf("Informe a quantidade de pessoas: ");
    scanf("%f", &num);

    printf("\nValor do ingresso\t\tValor total recebido\n");
    for(i=1; i<=num; i++)
    {
        printf("R$ %.2f\t\t\t\tR$ %.2f\n", j, 10*j);
        j+=0.5;
    }
}
