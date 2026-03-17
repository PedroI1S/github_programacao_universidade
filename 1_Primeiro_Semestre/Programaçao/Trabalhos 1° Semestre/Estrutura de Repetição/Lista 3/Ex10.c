#include <stdio.h>

int main (void)
{
    int sup, inf, i=0, j=0, k=0, media=0, primo=0, cont=0;

    do
    {
        printf("Informe um limite superior: ");
        scanf("%d", &sup);
    }while(sup<=0);
    do
    {
        printf("Informe um limite inferior: ");
        scanf("%d", &inf);
    }while(inf<=0);

    for(i=inf; i<sup; i++)
    {
        for(k=2; k<i; k++)
        {
            if(i%k==0)
            {
                primo=1;
            }
        }
        if(primo==0 && i!=1)
        {
            printf("%-5d", i);
            j++;

            if(j%5==0)
            {
                printf("\n");
            }
        }
        if(i%3==0 && i%7==0)
            {
                media= media+i;
                cont++;
            }

        primo=0;
    }
    if(cont>0)
    {
        printf("\n\nMedia dos multiplos de 3 e 7 no intervalo: %.2f \n", (float)media/cont);
    }
    else
    {
        printf("\n\nNenhum numero multiplo de 3 e 7 no intervalo\n");
    }

    return 0;
}
