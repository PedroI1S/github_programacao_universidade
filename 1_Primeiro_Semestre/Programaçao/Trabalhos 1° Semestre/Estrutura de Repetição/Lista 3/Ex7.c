#include <stdio.h>

int main (void)
{
    int num, i=1, j=0;
    long long unsigned int produto=1;

    printf("Insira o numero de linhas: ");
    scanf("%d", &num);

    while (num>=j)
    {
        while(i<(j+1))
        {
            produto=produto*i;
            if(i==1)
            {
                printf("!%d\t= ", j);
            }

            printf("%-5d", i);

            if(i==j)
            {
                printf(" = %lld", produto);
            }
            i++;
        }
        produto=1;
        i=1;
        printf("\n");
        j++;
    }
}
