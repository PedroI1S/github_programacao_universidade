#include <stdio.h>

int main (void)
{
    int num, i=0, j=1;

    printf("Informe uma quantidade: ");
    scanf("%d", &num);

    num++;

    for(num>0; num>=0; num--)
    {

        printf("  %d  ", i+j);
        i=i+j;
        j=i-j;

    }


}
