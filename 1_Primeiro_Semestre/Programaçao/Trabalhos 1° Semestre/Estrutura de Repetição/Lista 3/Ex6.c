#include <stdio.h>

int main (void)
{
    int num, i=0, j=0, k=1;

    printf("Informe um numero positivo: ");
    scanf("%d", &num);

    while (num>=j)
    {
        while(i<j)
        {
            printf("%-5d", k);
            k++;
            i++;
        }
        i=0;
        printf("\n");
        j++;
    }
}
