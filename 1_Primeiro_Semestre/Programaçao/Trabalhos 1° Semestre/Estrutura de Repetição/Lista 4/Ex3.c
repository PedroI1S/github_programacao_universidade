#include<stdio.h>

int main (void)
{
    int liminf, limsup, i=2, primo=0, somadig;
    char ch;


    do
    {
        do
        {
            printf("digite um valor positivo para o limite inferior do intervalo: ");
            scanf("%d", &liminf);
        }while(liminf<0);
        do
        {
            printf("digite um valor positivo para o limite superior do intervalo: ");
            scanf("%d", &limsup);
        }while(limsup<0);

        while(liminf<limsup)
        {
            while(i<liminf)
                {
                    if(liminf%i==0)
                    {
                        primo=1;
                    }
                    i++;
                }

                i=liminf;

                do
                {
                    somadig+=i%10;
                    i=i/10;
                }while(i>0);

                if(primo==0)
                {
                    printf("Primo %d => Soma dos digitos = %d \n", liminf, somadig);
                }

                primo=0;
                somadig=0;
                i=2;
                liminf++;

        }
        printf("\n\nDeseja continuar no programa: ");
        scanf(" %c", &ch);

    }while(ch=='s' || ch=='S');

}
