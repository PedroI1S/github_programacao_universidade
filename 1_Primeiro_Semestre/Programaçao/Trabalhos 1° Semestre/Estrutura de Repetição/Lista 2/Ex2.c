#include <stdio.h>

int main (void)
{
    int num, i=1, valor=0;

    printf("quantos numeros que mostrar: ");
    scanf("%d", &num);

    for(num>0; num>=0; num--)
    {
        printf(" %-8d", valor );

        valor+=2;

        if (i%5==0)
        {
            printf("\n");
        }
        i++;
    }
}
