#include <stdio.h>

int main (void)
{
    int num, primo=0, i=2, j=2, cont=0, numd=0;
    char ch;

    do
    {

        do
        {
            printf("informe um numero positivo: ");
            scanf("%d", &num);
        }
        while(num<0);

        numd=num+10;

        while(num<=numd)
        {
            printf("%d ==>", num);
            while(j<=num)
            {
                while(i<j)
                {
                    if(j%i==0)
                    {
                        primo=1;
                    }
                    i++;
                }
                if(primo==0)
                {
                    printf("%-3d", j);
                    cont++;
                }
                primo=0;
                i=2;
                j++;
            }
            j=2;
            num++;
            printf(" ==> %d primo(s)\n", cont);
            cont=0;
        }
        printf("\n\nDeseja continuar no programa: ");
        scanf(" %c", &ch);
    }
    while(ch=='S'||ch=='s');
}
