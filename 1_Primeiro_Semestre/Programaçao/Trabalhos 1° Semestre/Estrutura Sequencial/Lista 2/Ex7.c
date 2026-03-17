#include<stdio.h>

int main (void)
{
    float x;

    printf("insira o valor de x:");
    scanf("%f", &x);

    if(x<0)
    {
        printf("\n2x + 4\n");
        printf("2(%.1f) + 4\n", x);
        printf("%.1f + 4\n", x*2);
        printf("%.1f", (x*2)+4);
    }
    else
    {
        printf("\nx + 1\n");
        printf("%.1f + 1\n", x);
        printf("%.1f", x+1);
    }

    return 0;
}
