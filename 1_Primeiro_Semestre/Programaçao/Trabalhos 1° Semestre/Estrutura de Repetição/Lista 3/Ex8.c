#include <stdio.h>>

int main (void)
{
    int num, j, i=1, contador=0;
    char ch;

    do
    {
        printf("Informe um numero de 1 a 100: ");
        scanf("%d", &num);
        j=num;
        while(j<=(num+10))
        {
            printf("%-2d ==> ", j);

            while(i<=j)
            {
                if(j%i==0)
                {
                    printf("%d, ", i);
                    contador++;
                }
                i++;
            }
            printf(" %d divisore(s).\n", contador);
            i=1;
            contador=0;
            j++;
        }
        printf("\n\nDeseja continuar o programa (S/N): ");
        scanf(" %c", &ch);
    }
    while(ch=='s'||ch=='S');
}
