#include <stdio.h>

int main (void)
{
    int num, j, i;
    char ch;

    do
    {
        i=0;
        j=0;
        num=1;

        do
        {
            printf("Quantos numeros divisiveis por 3 mostrar: ");
            scanf("%d", &num);
        }
        while(num==0);

        if(num<0)
        {
            num=-num;
        }
        while(i<num)
        {
            if((j*3)%2==0)
            {
                printf("%-8d", j*3);
                i++;
            }
            j++;
        }
        printf("\n\nDeseja continuar no programa (s/n): ");
        scanf(" %c", &ch);
    }
    while(ch=='s'||ch=='S');

        return 0;
}
